#ifndef GEN_POLYGON_PATTERN_SYM_HPP
#define GEN_POLYGON_PATTERN_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/polygon_pattern_symbolizer.hpp>

#include "make_opt_funcs.hpp"

namespace cssgen {

static const mapnik::polygon_pattern_symbolizer pp_dfl(mapnik::parse_path(""));

}

BOOST_FUSION_ADAPT_ADT(
    mapnik::polygon_pattern_symbolizer,
    // polygon-pattern-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
    // polygon-pattern-alignment
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_alignment().as_string(),
                                    cssgen::pp_dfl.get_alignment().as_string()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct polygon_pattern_sym_gen : karma::grammar< Iter, mapnik::polygon_pattern_symbolizer() > {
        polygon_pattern_sym_gen() : polygon_pattern_sym_gen::base_type(polygon_pattern_sym) {
            
            using karma::string;
        
            polygon_pattern_sym =    -("polygon-pattern-file: "      << qstring << ";\n")
                                  << -("polygon-pattern-alignment: " << string  << ";\n");
        }
        
        quoted_string< Iter > qstring;
        karma::rule< Iter, mapnik::polygon_pattern_symbolizer() > polygon_pattern_sym;
    };
}

#endif