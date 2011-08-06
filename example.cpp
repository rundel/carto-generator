#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/config_error.hpp>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include <mapnik/save_map.hpp>
#include <mapnik/load_map.hpp>

#include <iostream>
#include <fstream>

#include "prettify.hpp"
#include "gen_map.hpp"


int main ( int argc , char** argv) {    
    
    namespace po = boost::program_options;
    
    std::string mapnik_input_dir = MAPNIKDIR;
    
    using namespace mapnik;
    try {

        std::string xml_file_name;
        std::string mml_file_name;
        std::string mss_file_name("style.mss");
        
        po::options_description desc("xml2carto");
        desc.add_options()
            ("help,h", "produce usage message")
            ("version,V","print version string")
            ("xml", po::value<std::string>(&xml_file_name), "input mapnik xml")   
            ("mml",po::value<std::string>(&mml_file_name),"output carto mml")
            ;
        
        std::string usage("\nusage: xml2carto map.xml map.mml");
        
        po::positional_options_description p;
        p.add("xml",1);
        p.add("mml",2);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
        
        if (vm.count("version"))
        {
            std::cout << "version 0.0.0" << std::endl;
            return 1;
        }

        if (vm.count("help")) 
        {
            std::cout << desc << usage << std::endl;
            return 1;
        }

        if (!vm.count("xml") || !boost::algorithm::ends_with(xml_file_name,".xml"))
        {
            std::cout << "Please provide an input xml\n" << std::endl;
            std::cout << desc << usage << std::endl;
            return 1;
        }

        if (!vm.count("mml") || !boost::algorithm::ends_with(mml_file_name,".mml"))
        {
            std::cout << "Please provide an output mml\n" << std::endl;
            std::cout << desc << usage << std::endl;
            return 1;
        }
        
        datasource_cache::instance()->register_datasources(mapnik_input_dir); 
        
        Map m(256,256);
        load_map(m,xml_file_name,false);
        
        typedef std::back_insert_iterator<std::string> iter;
        
        std::string mml;
        iter sink(mml);
        cssgen::mml_gen< iter > g_mml;
        
        cssgen::map_data md(m);
                
        bool r = boost::spirit::karma::generate(sink, g_mml, md);
        if (r) {
            std::ofstream mml_file;
            mml_file.open(mml_file_name.c_str());
            if (!mml_file.is_open()){
                std::cout << "error: could not save mml to: " << mml_file_name << "\n";
                return EXIT_FAILURE;
            }
            mml_file << prettify(mml);
            mml_file.close();
        }
        else
            std:: cout << "mml generator failed!\n";
                
        std::string mss;
        sink = iter(mss);
        cssgen::mss_gen< iter > g_mss;
        
        r = boost::spirit::karma::generate(sink, g_mss, md);
        
        if (r) {
            std::ofstream mss_file;
            mss_file.open(mss_file_name.c_str());
            if (!mss_file.is_open()){
                std::cout << "error: could not save mss to: " << mss_file_name << "\n";
                return EXIT_FAILURE;
            }
            mss_file << prettify(mss);
            mss_file.close();
        }
        else
            std:: cout << "mss generator failed!\n";
    }
    catch ( const mapnik::config_error & ex )
    {
        std::cerr << "### Configuration error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch ( const std::exception & ex )
    {
        std::cerr << "### std::exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch ( ... )
    {
        std::cerr << "### Unknown exception." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
