#include "gen_symbolizers.hpp"

namespace cssgen {
    
template <typename Iter>
symbolizer_gen<Iter>::symbolizer_gen() : symbolizer_gen::base_type(symbolizer) {
        
    symbolizer =   building_sym | line_sym | line_patter_sym | markers_sym
                 | point_sym | polygon_sym | polygon_pattern_sym
                 | raster_sym | shield_sym | text_sym;
                         
}

}