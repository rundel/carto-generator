#ifndef GEN_BUILDING_SYM_HPP
#define GEN_BUILDING_SYM_HPP

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/color.hpp>
#include <mapnik/building_symbolizer.hpp>
#include <mapnik/expression_string.hpp>

#include "utility/make_opt_funcs.hpp"
#include "gen_utility.hpp"


BOOST_FUSION_ADAPT_ADT(
    mapnik::building_symbolizer,
    // building-fill
    (mapnik::color, mapnik::color, obj.get_fill(), /**/)
    // building-fill-opacity
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_opacity(),
                              mapnik::building_symbolizer().get_opacity()),
     /**/)
    // building-height
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>( mapnik::to_expression_string(*obj.height()) ),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;

    template <typename Iter>
    struct building_sym_gen : karma::grammar< Iter, mapnik::building_symbolizer() > {
        building_sym_gen();
        
        quoted_string< Iter > qstring;
        color_rgb< Iter > color;
        karma::rule< Iter, mapnik::building_symbolizer() > building_sym;
    };

}

#endif