#include "symbolizers/gen_line_sym_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::line_sym_gen<iter>;