#ifndef GEN_FONT_SET_HPP
#define GEN_FONT_SET_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/font_set.hpp>

#include "gen_utility.hpp"

namespace cssgen {

    typedef std::map<std::string,mapnik::font_set> font_set_map;
    typedef std::pair<std::string,mapnik::font_set> font_set_pair;

}

BOOST_FUSION_ADAPT_ADT(
    mapnik::font_set,
    (std::string const&, std::string const&, obj.get_name(), /**/ )
    (std::vector<std::string> const&, std::vector<std::string> const&, obj.get_face_names(), /**/)
);

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::font_set_pair,
    (std::string, first)
    (mapnik::font_set, second)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    using karma::string;
    using karma::omit;

    template <typename Iter>
    struct font_set_gen : karma::grammar< Iter, font_set_map() > {
        font_set_gen();

        quoted_string< Iter > qstring;
        
        karma::rule< Iter, font_set_map() > fs_map;
        karma::rule< Iter, font_set_pair() > fs_pair;
        karma::rule< Iter, mapnik::font_set() > fs;
    };
}

#endif