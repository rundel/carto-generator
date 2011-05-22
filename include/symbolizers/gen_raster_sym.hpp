#ifndef GEN_RASTER_SYM_HPP
#define GEN_RASTER_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/raster_symbolizer.hpp>

#include "utility/make_opt_funcs.hpp"

BOOST_FUSION_ADAPT_ADT(
    mapnik::raster_symbolizer,    
    // raster-opacity    
    (boost::optional<float>,
     boost::optional<float>,
     cssgen::make_opt<float>(obj.get_opacity(),
                             mapnik::raster_symbolizer().get_opacity()),
     /**/)
    // raster-mode
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>(obj.get_mode(),
                                   mapnik::raster_symbolizer().get_mode()),
     /**/)
    // raster-scaling
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>(obj.get_scaling(),
                                   mapnik::raster_symbolizer().get_scaling()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct raster_sym_gen : karma::grammar< Iter, mapnik::raster_symbolizer() > {
        raster_sym_gen() : raster_sym_gen::base_type(raster_sym) {
        
            using karma::float_;
            using karma::string;
        
            raster_sym =    -("raster-opacity: " << float_ << ";\n")
                         << -("raster-mode: "    << string << ";\n")
                         << -("raster-scaling: " << string << ";\n");
        }
        
        color_rgb< Iter > color;
        karma::rule< Iter, mapnik::raster_symbolizer() > raster_sym;
    };
}

#endif