#define FUSION_MAX_VECTOR_SIZE 15

#include "gen_symbolizers_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::symbolizer_gen<iter>;