#ifndef GEN_STYLE_HPP
#define GEN_STYLE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/rule.hpp>
#include <mapnik/expression_string.hpp>
#include <mapnik/feature_type_style.hpp>

#include "utility/zoom_funcs.hpp"
#include "utility/make_opt_funcs.hpp"
#include "gen_symbolizers.hpp"

namespace cssgen {

typedef std::map<std::string,mapnik::rules > style_map;
typedef std::pair<std::string,mapnik::rules > style_pair;

}


BOOST_FUSION_ADAPT_STRUCT(
    cssgen::style_pair,
    (std::string, first)
    (mapnik::rules, second)
);


BOOST_FUSION_ADAPT_ADT(
    mapnik::rule,
    // name
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_name(),mapnik::rule().get_name()), /**/)
    // filter
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(mapnik::to_expression_string(*obj.get_filter()),
                                   mapnik::to_expression_string(*mapnik::rule().get_filter()) ), /**/)
    // zoom levels
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::conv_zoom(
        cssgen::make_opt<double>(obj.get_min_scale(),mapnik::rule().get_min_scale()),
        cssgen::make_opt<double>(obj.get_max_scale(),mapnik::rule().get_max_scale())), /**/)
    //(bool,   bool,   obj.has_else_filter(), /**/)
    // symbolizers
    (mapnik::rule::symbolizers const&, mapnik::rule::symbolizers const&,  obj.get_symbolizers(), /**/)
);



namespace cssgen {

namespace karma = boost::spirit::karma;

template <typename Iter>
struct style_gen : karma::grammar< Iter, style_map() > {
    style_gen();

    quoted_string< Iter > qstring;
    symbolizer_gen< Iter > symbolizer;

    karma::rule< Iter, style_map() >  styles;
    karma::rule< Iter, style_pair() > style;
    karma::rule< Iter, mapnik::rules() > rules;
    karma::rule< Iter, mapnik::rule() > rule;
};

}

#endif