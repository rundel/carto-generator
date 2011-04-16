#include <boost/algorithm/string.hpp>

namespace cssgen {

struct layer_data {
    std::string id_;
    std::string name_;
    std::string srs_;
    
    std::vector<std::string>  style_names_;
    style_map styles_;
    
    boost::optional<std::string> title_;
    boost::optional<std::string> abstract_;
        
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
        
        
        if (rhs.title() != "")
            title_ = rhs.title();
        if (rhs.abstract() != "")
            abstract_ = rhs.abstract();
        
        if (defaults.getMinZoom() != rhs.getMinZoom())
            minZoom_ = rhs.getMinZoom();
        if (defaults.getMaxZoom() != rhs.getMaxZoom())
            maxZoom_ = rhs.getMaxZoom();
        
        if (defaults.isActive() != rhs.isActive())
            active_ = rhs.isActive();
        if (defaults.isQueryable() != rhs.isQueryable())
            queryable_ = rhs.isQueryable();
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
    (boost::optional<std::string>, title_)    
    (boost::optional<std::string>, abstract_)
    (boost::optional<double>, minZoom_)
    (boost::optional<double>, maxZoom_)
    (boost::optional<bool>, active_)
    (boost::optional<bool>, queryable_)
    (boost::optional<bool>, clear_label_cache_)
    //(boost::optional<bool>, cache_features_)
    //(std::vector<std::string>, style_names_)
    (mapnik::parameters, datasource_params_)
);

BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(
    cssgen::layer_data const, 
    (cssgen),
    layer_style,
    (std::string, id_)
    //(std::vector<std::string>, style_names_)
);


namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    using karma::double_;
    using karma::bool_;
    using karma::string;
    using karma::omit;
    using karma::lit;

    template <typename Iter>
    struct layer_mml_gen : karma::grammar< Iter, layer_mml() > {
        layer_mml_gen() : layer_mml_gen::base_type(layer) {

            //styles = "Styles: " << qstring % ",\n" << "\n";
            layer =     ("\"id\": " << qstring << "," << "\n")
                    <<  ("\"name\": " << qstring << "," << "\n")
                    <<  ("\"srs\": " << qstring << "," << "\n")
                    << -("\"title\": " << qstring << "," << "\n")
                    << -("\"abstract\": " << qstring << "," << "\n")
                    << -("\"minZoom\": " << double_ << "," << "\n") 
                    << -("\"maxZoom\": " << double_ << "," << "\n") 
                    << -("\"active\": " << bool_ << "," << "\n") 
                    << -("\"queryable\": " << bool_ << "," << "\n")
                    << -("\"clear-label-cache\": " << bool_ << "," << "\n") 
                    //<< -("\"cache_features\": " << bool_ << "\n")
                    //<< omit[styles]
                    <<  ( "\"datasources\": {\n" 
                          << datasource << "\n"
                    <<  ("}\n") );
        }
    
        quoted_string< Iter > qstring;
        
        parameter_css_gen< Iter > datasource;
        //karma::rule< Iter, std::vector<std::string>() > styles;
        karma::rule< Iter, layer_mml() > layer;
    };


    template <typename Iter>
    struct layer_mss_gen : karma::grammar< Iter, layer_style() > {
        layer_mss_gen() : layer_mss_gen::base_type(layer) {

            styles = "Styles: " << qstring % ",\n" << "\n";
            
            layer =    ("#" << qstring << " {\n")
                    << ("}\n");
        }
    
        quoted_string< Iter > qstring;
        
        parameter_css_gen< Iter > datasource;
        karma::rule< Iter, std::vector<std::string>() > styles;
        karma::rule< Iter, layer_style() > layer;
    };
}