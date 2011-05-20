#include "gen_line_pattern_sym.hpp"

namespace cssgen {

template <typename Iter>
line_pattern_sym_gen<Iter>::line_pattern_sym_gen() : line_pattern_sym_gen::base_type(line_pattern_sym) {

    line_pattern_sym = -("line-pattern-file: "      << qstring   << ";\n");
    
}

}