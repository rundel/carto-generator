#ifndef GEN_UTILITY_HPP
#define GEN_UTILITY_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/color.hpp>

BOOST_FUSION_ADAPT_ADT(
    mapnik::color,
    (unsigned, unsigned, obj.red(),   /**/)
    (unsigned, unsigned, obj.green(), /**/)
    (unsigned, unsigned, obj.blue(),  /**/)
    (bool,     bool,     obj.alpha()!=255, /**/)
    (unsigned, unsigned, obj.alpha(), /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct quoted_string : karma::grammar< Iter, std::string() > {
        quoted_string();
        karma::rule< Iter, std::string() > str;
    };

    template <typename Iter>
    struct color_hex : karma::grammar< Iter, mapnik::color() > {
        color_hex();
        karma::rule< Iter, mapnik::color() > c;
    };

    template <typename Iter>
    struct color_rgb : karma::grammar< Iter, mapnik::color() > {
        color_rgb();
        karma::rule< Iter, mapnik::color() > c;
    };
}


#endif