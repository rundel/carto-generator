#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/config_error.hpp>

#include <mapnik/save_map.hpp>
#include <mapnik/load_map.hpp>

#include <iostream>

#include "prettify.hpp"
#include "gen_map.hpp"


int main ( int argc , char** argv) {    
    
    std::string mapnik_input_dir = MAPNIKDIR;
    std::string mapnik_font_dir = mapnik_input_dir + "/../fonts/";
    
    //mapnik_dir += "/lib/mapnik2/";
    std::string xml_file = (argc == 2) ? std::string(argv[1]) : "map.xml";
    
    using namespace mapnik;
    try {
        
        std::cout << " running demo ... \n";
        std::cout << " looking for 'shape.input' plugin in... " << mapnik_input_dir << "\n";
        datasource_cache::instance()->register_datasources(mapnik_input_dir); 
        
        //std::cout << " looking for DejaVuSans font in... " << mapnik_font_dir << "\n";
        //freetype_engine::register_fonts(mapnik_font_dir);
        
        Map m(800,600);
        load_map(m,xml_file,true);
        
        typedef std::back_insert_iterator<std::string> iter;
        
        std::string mml;
        iter sink(mml);
        cssgen::mml_gen< iter > g_mml;
        
        cssgen::map_data md(m);
        
        std::cout << "-------------------------\n";
        std::cout << "mml:\n\n";
        
        bool r = boost::spirit::karma::generate(sink, g_mml, md);
        if (r)
            std::cout << prettify(mml) << "\n";
        else
            std:: cout << "mml generator failed!\n";
        
        std::cout << "\n-------------------------\n";
        std::cout << "mss:\n\n";
        
        std::string mss;
        sink = iter(mss);
        cssgen::mss_gen< iter > g_mss;
        
        r = boost::spirit::karma::generate(sink, g_mss, md);
        
        if (r)
            std::cout << prettify(mss) << "\n";
        else
            std:: cout << "mss generator failed!\n";
        
        std::cout << "\n-------------------------\n";

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
