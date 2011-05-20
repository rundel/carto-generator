#ifndef GEN_POINT_SYM_HPP
#define GEN_POINT_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/point_symbolizer.hpp>

#include "make_opt_funcs.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::point_symbolizer,
    // point-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
    // point-allow-overlap
    (boost::optional<bool>,
     boost::optional<bool>,
     cssgen::make_opt<bool>(obj.get_allow_overlap(),
                            mapnik::point_symbolizer().get_allow_overlap()),
     /**/)
    // point-ignore-placement
    (boost::optional<bool>,
     boost::optional<bool>,
     cssgen::make_opt<bool>(obj.get_ignore_placement(),
                            mapnik::point_symbolizer().get_ignore_placement()),
     /**/)
    // point-placement
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_point_placement().as_string(),
                                    mapnik::point_symbolizer().get_point_placement().as_string()),
     /**/)
    // point-transform
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_transform_string(),
                                    mapnik::point_symbolizer().get_transform_string()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct point_sym_gen : karma::grammar< Iter, mapnik::point_symbolizer() > {
        point_sym_gen() : point_sym_gen::base_type(point_sym) {
            
            using karma::string;
            using karma::bool_;
        
            point_sym =    -("point-file: "             << qstring << ";\n")
                        << -("point-allow-overlap: "    << bool_   << ";\n")
                        << -("point-ignore-placement: " << bool_   << ";\n")
                        << -("point-placement: "        << string  << ";\n")
                        << -("point-transform: "        << string  << ";\n");
        }
        
        quoted_string< Iter > qstring;
        karma::rule< Iter, mapnik::point_symbolizer() > point_sym;
    };
}

#endif