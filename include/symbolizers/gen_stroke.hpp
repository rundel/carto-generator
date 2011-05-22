#ifndef GEN_STROKE_HPP
#define GEN_STROKE_HPP

#include <boost/fusion/include/adapt_adt.hpp>

#include <mapnik/stroke.hpp>

#include "utility/make_opt_funcs.hpp"
#include "gen_dash_pair.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::stroke,
    // color
    (boost::optional<mapnik::color>,
     boost::optional<mapnik::color>,
     cssgen::make_opt<mapnik::color>(obj.get_color(),
                                     mapnik::stroke().get_color()), 
     /**/)
    // width
    (double, double, obj.get_width(), /**/)
    // opacity
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_opacity(),
                              mapnik::stroke().get_opacity()),
     /**/)
    // linejoin
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>(obj.get_line_join().as_string(),
                                   mapnik::stroke().get_line_join().as_string()),
     /**/)
    // linecap
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>(obj.get_line_cap().as_string(),
                                   mapnik::stroke().get_line_cap().as_string()),
     /**/)
    // gamma
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_gamma(),
                              mapnik::stroke().get_gamma()),
     /**/)
    // dasharray
    (boost::optional<mapnik::dash_array>, boost::optional<mapnik::dash_array>,
     cssgen::make_opt_has<mapnik::dash_array>(obj.get_dash_array(),
                                              obj.has_dash()),
     /**/)
);


#endif