#include "gen_map_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::mml_gen<iter>;
template struct cssgen::mss_gen<iter>;