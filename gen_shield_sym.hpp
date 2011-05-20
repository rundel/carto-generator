#ifndef GEN_SHIELD_SYM_HPP
#define GEN_SHIELD_SYM_HPP

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <mapnik/shield_symbolizer.hpp>
#include <mapnik/expression_string.hpp>

#include "make_opt_funcs.hpp"

namespace cssgen {

static const mapnik::shield_symbolizer sh_dfl(mapnik::expression_ptr(), 
                                              "<no default>", 
                                              0, 
                                              mapnik::color(0,0,0), 
                                              mapnik::path_expression_ptr());

}



BOOST_FUSION_ADAPT_ADT(
    mapnik::shield_symbolizer,
    // shield-name
    (boost::optional<std::string>, 
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>( mapnik::to_expression_string(*obj.get_name()) ),
     /**/)
    // shield-face-name
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>( obj.get_face_name() ), 
     /**/)
    // shield-face-name
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>( obj.get_fontset().get_name() ),
     /**/)
    // shield-size
    (unsigned, unsigned, obj.get_text_size(), /**/ )
    // shield-fill
    (boost::optional<mapnik::color>, 
     boost::optional<mapnik::color>,
     cssgen::make_opt<mapnik::color>(obj.get_fill(),
                                     cssgen::sh_dfl.get_fill()),
     /**/)
    // shield-min-distance
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_minimum_distance(),
                              cssgen::sh_dfl.get_minimum_distance()),
     /**/)
    // shield-spacing
    (boost::optional<unsigned>,
     boost::optional<unsigned>,
     cssgen::make_opt<unsigned>(obj.get_label_spacing(),
                                cssgen::sh_dfl.get_label_spacing()),
     /**/)
    // shield-character-spacing
    (boost::optional<unsigned>,
     boost::optional<unsigned>,
     cssgen::make_opt<unsigned>(obj.get_character_spacing(),
                                cssgen::sh_dfl.get_character_spacing()),
     /**/)
    // shield-line-spacing
    (boost::optional<unsigned>, 
     boost::optional<unsigned>,
     cssgen::make_opt<unsigned>(obj.get_line_spacing(),
                                cssgen::sh_dfl.get_line_spacing()),
     /**/)
    // shield-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
    // shield-text-dx
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_displacement().get<0>(),
                              cssgen::sh_dfl.get_displacement().get<0>()),
     /**/)
    // shield-text-dy
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_displacement().get<1>(),
                              cssgen::sh_dfl.get_displacement().get<1>()),
     /**/)
    // shield-dx
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_shield_displacement().get<0>(),
                              cssgen::sh_dfl.get_shield_displacement().get<0>()),
     /**/)
    // shield-dy
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_shield_displacement().get<1>(),
                              cssgen::sh_dfl.get_shield_displacement().get<1>()),
     /**/)
);



namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct shield_sym_gen : karma::grammar< Iter, mapnik::shield_symbolizer() > {
        shield_sym_gen() : shield_sym_gen::base_type(shield_sym) {
        
            using karma::double_;
            using karma::string;
            using karma::uint_;
        
            shield_sym =     ("shield-name: "                << qstring << ";\n")
                         << -("shield-face-name: "           << qstring << ";\n")
                         << -("shield-face-name: @"          << string  << ";\n")
                         << -("shield-size: "                << uint_   << ";\n")
                         << -("shield-fill: "                << color   << ";\n")
                         << -("shield-min-distance: "        << double_ << ";\n")
                         << -("shield-spacing: "             << uint_   << ";\n")
                         << -("shield-character-spacing: "   << uint_   << ";\n")
                         << -("shield-line-spacing: "        << uint_   << ";\n")
                         << -("shield-file: "                << qstring << ";\n")
                         << -("shield-text-dx: "             << double_ << ";\n")
                         << -("shield-text-dy: "             << double_ << ";\n")
                         << -("shield-dx: "                  << double_ << ";\n")
                         << -("shield-dy: "                  << double_ << ";\n");
        
        }
        quoted_string< Iter > qstring;
        color_rgb< Iter > color;
        
        karma::rule< Iter, mapnik::shield_symbolizer() > shield_sym;
    };
}

#endif