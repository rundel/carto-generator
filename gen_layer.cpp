#define FUSION_MAX_VECTOR_SIZE 12

#include "gen_layer_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::layer_mml_gen<iter>;
template struct cssgen::layer_mss_gen<iter>;