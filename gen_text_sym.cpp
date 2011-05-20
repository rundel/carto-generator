#define FUSION_MAX_VECTOR_SIZE 25

#include "gen_text_sym_def.hpp"

typedef std::back_insert_iterator<std::string> iter;
template struct cssgen::text_sym_gen<iter>;