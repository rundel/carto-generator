#include "gen_map.hpp"

namespace cssgen {

template <typename Iter>
mml_gen<Iter>::mml_gen() : mml_gen::base_type(mml) {
    
    using karma::omit;
    using karma::int_;
    
    mml =    omit[-font_sets]
          << "{\n"
          << "\"srs\": " << qstring << ",\n"
          << omit[qstring]
          << omit[color]
          << omit[-int_]
          << "\"Stylesheet\": [\n"
          << "\"style.mss\"\n"
          << "],\n"
          << "\"Layer\": [\n" 
          << ("{\n" << layer << "}") % ",\n" << "\n"
          << "]\n"
          << "}";
}

template <typename Iter>
mss_gen<Iter>::mss_gen() : mss_gen::base_type(mms) {
    
    using karma::int_;
    
    mms =    -font_sets
          << "\n"
          << "Map {\n"
          << "srs: " << qstring << ";\n"
          << -("background-image: " << qstring << ";\n")
          << -("background-color: " << color << ";\n")
          << -("buffer-size: " << int_ << ";\n")
          << "}\n"
          << "\n"
          << layer % "\n";
}

}