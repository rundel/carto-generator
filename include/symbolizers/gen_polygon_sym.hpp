#ifndef GEN_POLYGONSYM_HPP
#define GEN_POLYGONSYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/polygon_symbolizer.hpp>

#include "utility/make_opt_funcs.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::polygon_symbolizer,
    // polygon-fill
    (mapnik::color, mapnik::color, obj.get_fill(), /**/)
    // polygon-gamma
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_gamma(),
                              mapnik::polygon_symbolizer().get_gamma()),
     /**/)
    // polygon-opacity
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_opacity(),
                              mapnik::polygon_symbolizer().get_opacity()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct polygon_sym_gen : karma::grammar< Iter, mapnik::polygon_symbolizer() > {
        polygon_sym_gen() : polygon_sym_gen::base_type(polygon_sym) {
        
            using karma::double_;
        
            polygon_sym =     ("polygon-fill: "      << color   << ";\n")
                       << -("polygon-gamma: "     << double_ << ";\n")
                       << -("polygon-opacity: "   << double_ << ";\n");
        }
        
        color_rgb< Iter > color;
        karma::rule< Iter, mapnik::polygon_symbolizer() > polygon_sym;
    };
}

#endif