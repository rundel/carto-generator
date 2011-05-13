#include "gen_stroke.hpp"

#include "gen_line_sym.hpp"
#include "gen_polygon_sym.hpp"
#include "gen_text_sym.hpp"
#include "gen_markers_sym.hpp"

namespace cssgen {

namespace karma = boost::spirit::karma;

template <typename Iter>
struct symbolizer_gen : karma::grammar< Iter, mapnik::symbolizer() > {
    symbolizer_gen() : symbolizer_gen::base_type(symbolizer) {
            
        symbolizer = poly_sym | line_sym | text_sym | markers_sym;
        
    }

    line_sym_gen< Iter > line_sym;
    poly_sym_gen< Iter > poly_sym;
    text_sym_gen< Iter > text_sym;
    markers_sym_gen< Iter > markers_sym;

    karma::rule< Iter, mapnik::symbolizer() > symbolizer;
    
};

}