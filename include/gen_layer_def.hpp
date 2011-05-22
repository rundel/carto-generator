#include "gen_layer.hpp"

namespace cssgen {

template <typename Iter>
layer_mml_gen<Iter>::layer_mml_gen() : layer_mml_gen::base_type(layer) {
    
    using karma::double_;
    using karma::bool_;
    
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
            <<  ("\"datasources\": {\n" 
                  << datasource << "\n"
            <<  "}\n" );
}

template <typename Iter>
layer_mss_gen<Iter>::layer_mss_gen() : layer_mss_gen::base_type(layer) {
    
    using karma::string;
    
    layer =    ("#" << string << " {\n")
            << (styles << "\n")
            << ("}\n");
}

}