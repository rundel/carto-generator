#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
//#include <mapnik/agg_renderer.hpp>
//#include <mapnik/filter_factory.hpp>
//#include <mapnik/image_util.hpp>
#include <mapnik/config_error.hpp>


#include <mapnik/save_map.hpp>
#include <mapnik/load_map.hpp>

#include <iostream>

//#include "generators.hpp"
#include "gen_map.hpp"

std::string prettify(std::string in, std::string indent = "    ") {
    
    std::string out;
    out.reserve(in.size());
    
    char cur, prev;
    bool in_quote = false;
    int depth = 0;
    
    std::string::iterator it;
    for(it=in.begin(); it<in.end(); ++it ) {
        
        cur = *it;
        
        if ((cur == '}' || cur == ']') && !in_quote)
            depth--;
        
        if (prev == '\n' && !in_quote) {
            int j=depth;
            while(j-- !=0 ) {
                out.append(indent);
            }
        }
        
        if ((cur == '{' || cur == '[') && !in_quote)
            depth++;
        
        if (cur == '"' && prev != '\\')
            in_quote = !in_quote;
        
        out.push_back(cur);
        
        prev = cur;
    }
    
    return out;
}


int main ( int argc , char** argv) {    
    std::string mapnik_dir, xml_file;
    
    
    xml_file = (argc > 1) ? std::string(argv[1]) : "map.xml";
    mapnik_dir = (argc == 3) ? std::string(argv[2]) : "/usr/local/lib/mapnik2/"; 
    
    using namespace mapnik;
    try {
        
        std::cout << " running demo ... \n";
        
        std::cout << " looking for 'shape.input' plugin in... " << mapnik_dir << "input/" << "\n";
        datasource_cache::instance()->register_datasources(mapnik_dir + "input/"); 
        
        std::cout << " looking for DejaVuSans font in... " << mapnik_dir << "fonts/DejaVuSans.ttf" << "\n";
        freetype_engine::register_font(mapnik_dir + "fonts/DejaVuSans.ttf");        
        freetype_engine::register_font(mapnik_dir + "fonts/DejaVuSans-Book.ttf");
        freetype_engine::register_font(mapnik_dir + "fonts/DejaVuSans-Bold.ttf");
        freetype_engine::register_font(mapnik_dir + "fonts/DejaVuSans-Oblique.ttf");
        freetype_engine::register_font("/Library/Fonts/Georgia.ttf");
        freetype_engine::register_font("/Library/Fonts/Microsoft/Arial Italic.ttf");
        
        
        Map m(800,600);
        load_map(m,xml_file,true);
        //m.set_background(color_factory::from_string("black"));
                
        //m.zoom_to_box(box2d<double>(1405120.04127408,-247003.813399447,
        //                             1706357.31328276,-25098.593149577));
        //
        //image_32 buf(m.width(),m.height());
        //agg_renderer<image_32> ren(m,buf);
        //ren.apply();
        //
        //save_to_file<image_data_32>(buf.data(),"demo.jpg","jpeg");
        //save_to_file<image_data_32>(buf.data(),"demo.png","png");
        //save_to_file<image_data_32>(buf.data(),"demo256.png","png256");
        //std::cout << "Three maps have been rendered using AGG in the current directory:\n"
        //          << "- demo.jpg\n"
        //          << "- demo.png\n"
        //          << "- demo256.png\n"
        //          << "Have a look!\n";
        
        
        cssgen::map_data md(m);
        
        
        typedef std::back_insert_iterator<std::string> iter;
        
        std::string mml;
        iter sink(mml);
        cssgen::mml_gen< iter > g_mml;
        
        
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
