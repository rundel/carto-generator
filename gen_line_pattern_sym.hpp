#ifndef GEN_LINE_PATTERN_SYM_HPP
#define GEN_LINE_PATTERN_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/line_pattern_symbolizer.hpp>

#include "make_opt_funcs.hpp"
#include "gen_utility.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::line_pattern_symbolizer,
    // line-pattern-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct line_pattern_sym_gen : karma::grammar< Iter, mapnik::line_pattern_symbolizer() > {
        line_pattern_sym_gen();
        
        quoted_string< Iter > qstring;
        karma::rule< Iter, mapnik::line_pattern_symbolizer() > line_pattern_sym;
    };
}

#endif