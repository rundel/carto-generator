#include "gen_font_set.hpp"

namespace cssgen {

template <typename Iter>
font_set_gen<Iter>::font_set_gen() : font_set_gen::base_type(fs_map) {
    
    fs = omit[string] << qstring % ", " << ";";
    fs_pair = "@" << string << ": " << fs;
    fs_map  = fs_pair % "\n" << "\n";
}
 
}