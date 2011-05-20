#include "gen_style.hpp"

namespace cssgen {

template <typename Iter>
style_gen<Iter>::style_gen() : style_gen::base_type(styles) {

    using karma::omit;
    using karma::string;
    using karma::double_;
    using karma::bool_;
    
    rule  =    -("." << string << " ")
            << -("[" << string << "] ")
            << -(string << " ")
            << "{\n"
            << -("title: " << qstring << ";\n")
            << -("abstract: " << qstring << ";\n")
            //<< -("else_filter: " << bool_ << ";\n")
            << symbolizer % ""
            
            << "}";
                  
    rules  = rule % "\n";
    style  =    "." << string << " {\n"
             << rules << "\n"
             << "}";
    styles = style % "\n";
}

}