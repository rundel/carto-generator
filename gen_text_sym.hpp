namespace cssgen {

namespace karma = boost::spirit::karma;

static const mapnik::text_symbolizer ts_dfl(mapnik::expression_ptr(), "<no default>", 0, mapnik::color(0,0,0) );

struct placement_ : karma::symbols<int,char const*>
{
    placement_()
    {
        add(0, "point")
           (1, "line")
           (2, "vertex")
           (3, "interior")
           (4, "");
    }
};
    
struct vert_align_ : karma::symbols<int,char const*>
{
    vert_align_()
    {
        add(0, "top")
           (1, "middle")
           (2, "bottom")
           (3, "auto")
           (4, "");
    }
};
    
struct horz_align_ : karma::symbols<int,char const*>
{
    horz_align_()
    {
        add(0, "left")
           (1, "middle")
           (2, "right")
           (3, "auto")
           (4, "");
    }
};    
    
struct justify_align_ : karma::symbols<int,char const*>
{
    justify_align_()
    {
        add(0, "left")
           (1, "middle")
           (2, "right")
           (3, "");
    }
};    

struct transform_ : karma::symbols<int,char const*>
{
    transform_()
    {
        add(0, "none")
           (1, "uppercase")
           (2, "lowercase")
           (3, "capitalize")
           (4, "");
    }
};

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
    (boost::optional<int>, boost::optional<int>, \
     cssgen::make_opt<int>(obj.get_label_placement(),cssgen::ts_dfl.get_label_placement()), /**/)
    (boost::optional<int>, boost::optional<int>, \
     cssgen::make_opt<int>(obj.get_vertical_alignment(),cssgen::ts_dfl.get_vertical_alignment()), /**/)
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
    (boost::optional<int>, boost::optional<int>, \
     cssgen::make_opt<int>(obj.get_text_transform(),cssgen::ts_dfl.get_text_transform()), /**/)
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
            
            text_sym =    -("text-name: "                      << qstring    << ";\n")
                       << -("text-face-name: "                 << qstring    << ";\n")
                       << -("text-face-name: "                 << qstring    << ";\n")
                       <<  ("text-size: "                      << uint_      << ";\n")
                       <<  ("text-fill: "                      << color      << ";\n")
                       << -("text-dx: "                        << double_    << ";\n")
                       << -("text-dy: "                        << double_    << ";\n")
                       << -("text-placement: "                 << placement  << ";\n")
                       << -("text-vertical-alignment: "        << vert_align << ";\n")
                       << -("text-halo-radius: "               << double_    << ";\n")
                       << -("text-halo-fill: "                 << color      << ";\n")
                       << -("text-ratio: "                     << uint_      << ";\n")
                       << -("text-wrap-width: "                << uint_      << ";\n")
                       //<< -( wrap-before                                      ";\n")
                       //<< -( wrap-char                                        ";\n")
                       << -("text-transform: "                 << transform  << ";\n")
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
        color_hex< Iter > color;
        
        placement_ placement;
        vert_align_ vert_align;
        transform_ transform;
        
        karma::rule< Iter, mapnik::text_symbolizer() > text_sym;
    
    };
}