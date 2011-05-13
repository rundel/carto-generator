namespace cssgen {

static const mapnik::text_symbolizer ts_dfl(mapnik::expression_ptr(), "<no default>", 0, mapnik::color(0,0,0) );

}


BOOST_FUSION_ADAPT_ADT(
    mapnik::text_symbolizer,
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt_empty<std::string>( mapnik::to_expression_string(*obj.get_name()) ), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt_empty<std::string>( obj.get_face_name() ), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt_empty<std::string>( obj.get_fontset().get_name() ), /**/)
    (unsigned, unsigned, obj.get_text_size(), /**/ )
    (mapnik::color const&, mapnik::color const&, obj.get_fill(), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_displacement().get<0>(),cssgen::ts_dfl.get_displacement().get<0>()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_displacement().get<1>(),cssgen::ts_dfl.get_displacement().get<1>()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_label_placement().as_string(),cssgen::ts_dfl.get_label_placement().as_string()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_vertical_alignment().as_string(),cssgen::ts_dfl.get_vertical_alignment().as_string()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_halo_radius(),cssgen::ts_dfl.get_halo_radius()), /**/)
    (boost::optional<mapnik::color>, boost::optional<mapnik::color>, \
     cssgen::make_opt<mapnik::color>(obj.get_halo_fill(),cssgen::ts_dfl.get_halo_fill()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_text_ratio(),cssgen::ts_dfl.get_text_ratio()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_wrap_width(),cssgen::ts_dfl.get_wrap_width()), /**/)
    // wrap_before() ?
    // wrap_char() ?
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_text_transform().as_string(),cssgen::ts_dfl.get_text_transform().as_string()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_line_spacing(),cssgen::ts_dfl.get_line_spacing()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_character_spacing(),cssgen::ts_dfl.get_character_spacing()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_label_position_tolerance(),cssgen::ts_dfl.get_label_position_tolerance()), /**/)
    (boost::optional<unsigned>, boost::optional<unsigned>, \
     cssgen::make_opt<unsigned>(obj.get_label_spacing(),cssgen::ts_dfl.get_label_spacing()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_minimum_distance(),cssgen::ts_dfl.get_minimum_distance()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_minimum_padding(),cssgen::ts_dfl.get_minimum_padding()), /**/)
    (boost::optional<bool>, boost::optional<bool>, \
     cssgen::make_opt<bool>(obj.get_allow_overlap(),cssgen::ts_dfl.get_allow_overlap()), /**/)
    (boost::optional<bool>, boost::optional<bool>, \
     cssgen::make_opt<bool>(obj.get_avoid_edges(),cssgen::ts_dfl.get_avoid_edges()), /**/)
    //(boost::optional<double>, boost::optional<double>, \
    // cssgen::make_opt<double>(obj.get_text_opacity(),mapnik::().get_text_opacity()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_max_char_angle_delta(),cssgen::ts_dfl.get_max_char_angle_delta()), /**/)
    // get_horizontal_alignment
    // get_justify_alignment
);



namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct text_sym_gen : karma::grammar< Iter, mapnik::text_symbolizer() > {
        text_sym_gen() : text_sym_gen::base_type(text_sym) {
            
            using karma::double_;
            using karma::bool_;
            using karma::uint_;
            using karma::string;
            
            text_sym =    -("text-name: "                      << qstring    << ";\n")
                       << -("text-face-name: "                 << qstring    << ";\n")
                       << -("text-face-name: @"                << string     << ";\n")
                       <<  ("text-size: "                      << uint_      << ";\n")
                       <<  ("text-fill: "                      << color      << ";\n")
                       << -("text-dx: "                        << double_    << ";\n")
                       << -("text-dy: "                        << double_    << ";\n")
                       << -("text-placement: "                 << string     << ";\n")
                       << -("text-vertical-alignment: "        << string     << ";\n")
                       << -("text-halo-radius: "               << double_    << ";\n")
                       << -("text-halo-fill: "                 << color      << ";\n")
                       << -("text-ratio: "                     << uint_      << ";\n")
                       << -("text-wrap-width: "                << uint_      << ";\n")
                       //<< -( wrap-before                                      ";\n")
                       //<< -( wrap-char                                        ";\n")
                       << -("text-transform: "                 << string     << ";\n")
                       << -("text-line-spacing: "              << uint_      << ";\n")
                       << -("text-character-spacing: "         << uint_      << ";\n")
                       << -("text-label-position-tolerance: "  << uint_      << ";\n")
                       << -("text-spacing: "                   << double_    << ";\n")                // FIXME - double check
                       << -("text-min-distance: "              << double_    << ";\n")
                       << -("text-min-padding: "               << double_    << ";\n")
                       << -("text-allow-overlap: "             << bool_      << ";\n")
                       << -("text-avoid-edges: "               << bool_      << ";\n")
                       //<< -( opacity                                          ";\n")
                       << -("text-max-char-angle-delta: "      << double_    << ";\n");
                       //<< -( horizontal_alignment
                       //<< -( justify_alignment
                     

        }
        
        quoted_string< Iter > qstring;
        color_rgb< Iter > color;
        
        karma::rule< Iter, mapnik::text_symbolizer() > text_sym;
    
    };
}