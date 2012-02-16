#include "gen_utility_def.hpp"

typedef std::back_insert_iterator<std::string> iter;

template struct cssgen::quoted_string<iter>;
template struct cssgen::color_hex<iter>;
template struct cssgen::color_rgb<iter>;