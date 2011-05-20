#include "gen_line_sym.hpp"

namespace cssgen {

template<typename Iter>
line_sym_gen<Iter>::line_sym_gen() : line_sym_gen::base_type(line_sym) {
    
    using karma::double_;
    using karma::string;
    
    stroke =    -("line-color: "     << color   << ";\n")
             <<  ("line-width: "     << double_ << ";\n")
             << -("line-opacity: "   << double_ << ";\n")
             << -("line-join: "      << string  << ";\n")
             << -("line-cap: "       << string  << ";\n")
             << -("line-gamma: "     << double_ << ";\n")
             << -("line-dasharray: " << dashpair % ", " << ";\n");
    
    dashpair = double_ << ", " << double_;
    
    line_sym = stroke;
}

}