#ifndef GEN_MAP_HPP
#define GEN_MAP_HPP

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/karma.hpp>

#include <mapnik/map.hpp>

#include "gen_utility.hpp"
#include "gen_font_set.hpp"
#include "gen_layer.hpp"


namespace cssgen {

struct map_data {       
    std::string  srs_;
    boost::optional<mapnik::color> background_;
    boost::optional<std::string> background_image_;
    boost::optional<int> buffer_size_;

    std::vector<layer_data> layers_; 

    boost::optional<font_set_map> fontsets_;

    map_data() {}

    map_data(const mapnik::Map& rhs) 
      : srs_(rhs.srs()),
          background_(rhs.background()),
          background_image_(rhs.background_image())
    {
        if (rhs.buffer_size() != mapnik::Map().buffer_size())
            buffer_size_ = rhs.buffer_size();
        
        BOOST_FOREACH(mapnik::layer const& lyr, rhs.layers()) {
            
            layer_data ld(lyr);
            
            std::map<std::string, mapnik::feature_type_style> fts_map = rhs.styles();
           
            BOOST_FOREACH(std::string const& style_name, lyr.styles()) {
                ld.styles_[style_name] = fts_map[style_name].get_rules();
            }
            
            layers_.push_back(ld);
            
        }
    
        if (!rhs.fontsets().empty())  {
            fontsets_ = rhs.fontsets();
        }
    }
};
}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::map_data,
    (boost::optional<cssgen::font_set_map>, fontsets_)
    (std::string, srs_ )
    (boost::optional<std::string>, background_image_ )
    (boost::optional<mapnik::color>, background_ )
    (boost::optional<int>, buffer_size_ )
    (std::vector<cssgen::layer_data>, layers_)
);




namespace cssgen {
    
    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct mml_gen : karma::grammar< Iter, map_data() > {
        mml_gen(std::string mss);
        
        quoted_string< Iter > qstring;
        color_rgb< Iter > color;
        layer_mml_gen< Iter > layer;
        font_set_gen< Iter > font_sets;
        karma::rule< Iter, map_data() > mml;
    };   


    template <typename Iter>
    struct mss_gen : karma::grammar< Iter, map_data() > {
        mss_gen();
        
        quoted_string< Iter > qstring;
        color_rgb< Iter > color;
        layer_mss_gen< Iter > layer;
        font_set_gen< Iter > font_sets;
        karma::rule< Iter, map_data() > mss;
        
    };

}

#endif