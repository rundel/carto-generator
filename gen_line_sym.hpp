#ifndef GEN_LINE_SYM_HPP
#define GEN_LINE_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/line_symbolizer.hpp>


#include "make_opt_funcs.hpp"
#include "gen_utility.hpp"
#include "gen_stroke.hpp"
#include "gen_dash_pair.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::line_symbolizer,
    (mapnik::stroke const&, mapnik::stroke const&, obj.get_stroke(), /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct line_sym_gen : karma::grammar< Iter, mapnik::line_symbolizer() > {
        line_sym_gen();
        
        color_rgb< Iter > color;
        
        karma::rule< Iter, dash_pair() > dashpair;
        
        karma::rule< Iter, mapnik::stroke() > stroke;
        karma::rule< Iter, mapnik::line_symbolizer() > line_sym;
        

    };
}

#endif