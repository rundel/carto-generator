#include "gen_font_set_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::font_set_gen<iter>;