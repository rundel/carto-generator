#include "gen_style_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::style_gen<iter>;