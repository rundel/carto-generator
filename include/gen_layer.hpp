#ifndef GEN_LAYER_HPP
#define GEN_LAYER_HPP


#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct_named.hpp>
#include <boost/spirit/include/karma.hpp>

#include <mapnik/layer.hpp>

#include "utility/make_opt_funcs.hpp"
#include "gen_utility.hpp"
#include "gen_style.hpp"
#include "gen_parameter.hpp"

namespace cssgen {

struct layer_data {
    std::string id_;
    std::string name_;
    std::string srs_;
    
    std::vector<std::string>  style_names_;
    style_map styles_;
    
    boost::optional<double> minZoom_;
    boost::optional<double> maxZoom_;
    boost::optional<bool> active_;
    boost::optional<bool> queryable_;
    boost::optional<bool> clear_label_cache_;
    boost::optional<bool> cache_features_;
    
    mapnik::parameters datasource_params_;
    
    
    
    layer_data() {}
    
    layer_data(const mapnik::layer& rhs) {
        mapnik::layer defaults("","");
        
        name_ = rhs.name();
        srs_ = rhs.srs();
        
        id_ = name_;
        boost::to_lower(id_);
        boost::replace_all(id_," ","_");
        
        style_names_ = rhs.styles();
        datasource_params_ = rhs.datasource()->params();
        
        
        if (defaults.min_zoom() != rhs.min_zoom())
            minZoom_ = rhs.min_zoom();
        if (defaults.max_zoom() != rhs.max_zoom())
            maxZoom_ = rhs.max_zoom();
        
        if (defaults.active() != rhs.active())
            active_ = rhs.active();
        if (defaults.queryable() != rhs.queryable())
            queryable_ = rhs.queryable();
        if (defaults.clear_label_cache() != rhs.clear_label_cache())
            clear_label_cache_ = rhs.clear_label_cache();
        if (defaults.cache_features() != rhs.cache_features())
            cache_features_ = rhs.cache_features();
    }
    
};
}



BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(
    cssgen::layer_data const, 
    (cssgen),
    layer_mml,
    (std::string, id_)
    (std::string, name_)
    (std::string, srs_ )
    (boost::optional<double>, minZoom_)
    (boost::optional<double>, maxZoom_)
    (boost::optional<bool>, active_)
    (boost::optional<bool>, queryable_)
    (boost::optional<bool>, clear_label_cache_)
    //(boost::optional<bool>, cache_features_)
    (mapnik::parameters, datasource_params_)
);

BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(
    cssgen::layer_data const, 
    (cssgen),
    layer_mss,
    (std::string, id_)
    (cssgen::style_map, styles_)
);


namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct layer_mml_gen : karma::grammar< Iter, layer_mml() > {
        layer_mml_gen();
    
        quoted_string< Iter > qstring;
        parameter_gen< Iter > datasource;
        karma::rule< Iter, layer_mml() > layer;
    };


    template <typename Iter>
    struct layer_mss_gen : karma::grammar< Iter, layer_mss() > {
        layer_mss_gen();
        
        quoted_string< Iter > qstring;
        style_gen< Iter> styles;
        karma::rule< Iter, layer_mss() > layer;
    };
}

#endif