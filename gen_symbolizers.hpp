#include "gen_stroke.hpp"

#include "gen_building_sym.hpp"
#include "gen_line_sym.hpp"
#include "gen_line_pattern_sym.hpp"
#include "gen_markers_sym.hpp"
#include "gen_point_sym.hpp"
#include "gen_polygon_sym.hpp"
#include "gen_polygon_pattern_sym.hpp"
#include "gen_raster_sym.hpp"
#include "gen_shield_sym.hpp"
#include "gen_text_sym.hpp"

namespace cssgen {

namespace karma = boost::spirit::karma;

template <typename Iter>
struct symbolizer_gen : karma::grammar< Iter, mapnik::symbolizer() > {
    symbolizer_gen() : symbolizer_gen::base_type(symbolizer) {
            
        symbolizer =   building_sym | line_sym | line_patter_sym | markers_sym
                     | point_sym | polygon_sym | polygon_pattern_sym
                     | raster_sym | shield_sym | text_sym;
                             
    }
    building_sym_gen<Iter>          building_sym;
    line_sym_gen<Iter>              line_sym;
    line_pattern_sym_gen<Iter>      line_patter_sym;
    markers_sym_gen<Iter>           markers_sym;
    point_sym_gen<Iter>             point_sym;
    polygon_sym_gen<Iter>           polygon_sym;
    polygon_pattern_sym_gen<Iter>   polygon_pattern_sym;
    raster_sym_gen<Iter>            raster_sym;
    shield_sym_gen<Iter>            shield_sym;        
    text_sym_gen<Iter>              text_sym;
    
    karma::rule< Iter, mapnik::symbolizer() > symbolizer;
    
};

}