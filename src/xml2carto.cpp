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


int main (int argc, char** argv) {    
    
    namespace po = boost::program_options;
    
    std::string mapnik_input_dir = MAPNIKDIR;
    
    std::string xml_file_name, mml_file_name, mss_file_name;
    
    po::options_description desc("xml2carto");
    desc.add_options()
        ("help,h", "produce usage message")
        ("version,V","print version string")
        ("xml", po::value<std::string>(&xml_file_name), "input mapnik xml")
        ("mml", po::value<std::string>(&mml_file_name), "output carto mml")
        ("mss", po::value<std::string>(&mss_file_name), "output carto mss")
        ;
    
    std::string usage("\nusage: xml2carto map.xml map.mml [map.mss]");
    
    po::positional_options_description p;
    p.add("xml",1).add("mml",1).add("mss",1);
    
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
        
    try {
        mapnik::datasource_cache::instance().register_datasources(mapnik_input_dir); 
        
        mapnik::Map m(256,256);
        mapnik::load_map(m,xml_file_name,false);
        
        typedef std::back_insert_iterator<std::string> iter;
        cssgen::map_data md(m);
        
        std::string mss;
        iter mss_sink(mss);
        cssgen::mss_gen< iter > g_mss;
        
        if (!boost::spirit::karma::generate(mss_sink, g_mss, md)) 
        {
            std:: cout << "Generation of stylesheet failed\n";
            return 1;
        }
        
        if (vm.count("mss"))
        {
            std::ofstream mss_file;
            mss_file.open(mss_file_name.c_str());
            if (!mss_file.is_open()){
                std::cout << "error: could not save mss to: " << mss_file_name << "\n";
                return EXIT_FAILURE;
            }
            mss_file << prettify(mss);
            mss_file.close();
        }


        std::string mml;
        iter mml_sink(mml);
        cssgen::mml_gen< iter > g_mml( (vm.count("mss")) ? mss_file_name : mss );
        
        if (boost::spirit::karma::generate(mml_sink, g_mml, md))
        {
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
            std:: cout << "Generation of " << mml_file_name << " failed!\n";
                

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
