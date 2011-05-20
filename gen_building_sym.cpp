#include "gen_building_sym_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::building_sym_gen<iter>;