
BOOST_FUSION_ADAPT_ADT(
    mapnik::markers_symbolizer,
    // marker-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
    // marker-opacity
    (boost::optional<float>,
     boost::optional<float>,
     cssgen::make_opt<float>( obj.get_opacity(),
                              mapnik::markers_symbolizer().get_opacity()),
     /**/)
    // marker-line-color, marker-line-width, marker-line-opacity
    (mapnik::stroke const&, mapnik::stroke const&, obj.get_stroke(), /**/)
    // marker-placement
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_marker_placement().as_string(),
                                    mapnik::markers_symbolizer().get_marker_placement().as_string()),
     /**/)
     // marker-type
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_marker_type().as_string(),
                                    mapnik::markers_symbolizer().get_marker_type().as_string()),
     /**/)
    // marker-width
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>( obj.get_width(),
                               mapnik::markers_symbolizer().get_width()),
     /**/)
    // marker-height
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>( obj.get_height(),
                               mapnik::markers_symbolizer().get_height()),
     /**/)
    // marker-fill
    (boost::optional<mapnik::color>,
     boost::optional<mapnik::color>,
     cssgen::make_opt<mapnik::color>( obj.get_fill(),
                                      mapnik::markers_symbolizer().get_fill()),
     /**/)
    // marker-allow-overlap
    (boost::optional<bool>,
     boost::optional<bool>,
     cssgen::make_opt<bool>( obj.get_allow_overlap(),
                             mapnik::markers_symbolizer().get_allow_overlap()),
     /**/)
    // marker-spacing
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>( obj.get_spacing(),
                               mapnik::markers_symbolizer().get_spacing()),
      /**/)
    // marker-max-error
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>( obj.get_max_error(),
                               mapnik::markers_symbolizer().get_max_error()),
     /**/)
    // marker-transform
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt<std::string>( obj.get_transform_string(),
                                    mapnik::markers_symbolizer().get_transform_string()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;

    template <typename Iter>
    struct markers_sym_gen : karma::grammar< Iter, mapnik::markers_symbolizer() > {
        markers_sym_gen() : markers_sym_gen::base_type(markers_sym) {

            using karma::double_;
            using karma::float_;
            using karma::bool_;
            using karma::string;

            stroke =    -("marker-line-color: "     << color   << ";\n")
                     << -("marker-line-width: "     << double_ << ";\n")
                     << -("marker-line-opacity: "   << double_ << ";\n");
                     //<< -("line-join: "      << string  << ";\n")
                     //<< -("line-cap: "       << string  << ";\n")
                     //<< -("line-gamma: "     << double_ << ";\n")
                     //<< -("line-dasharray: " << dashpair % ", " << ";\n");

            //dashpair = double_ << ", " << double_;

            markers_sym =    -("marker-file: "          << qstring << ";\n")
                          << -("marker-opacity: "       << float_  << ";\n")
                          <<  (stroke)
                          << -("marker-placement: "     << string  << ";\n")
                          << -("marker-type: "          << string  << ";\n")
                          << -("marker-width: "         << double_ << ";\n")
                          << -("marker-height: "        << double_ << ";\n")
                          << -("marker-fill: "          << color   << ";\n")
                          << -("marker-allow-overlap: " << bool_   << ";\n")
                          << -("marker-spacing: "       << double_ << ";\n")
                          << -("marker-max-error: "     << double_ << ";\n")
                          << -("marker-transform: "     << string  << ";\n");

        }

        quoted_string< Iter > qstring;
        color_rgb< Iter > color;

        //karma::rule< Iter, dash_pair() > dashpair;

        karma::rule< Iter, mapnik::stroke() > stroke;
        karma::rule< Iter, mapnik::markers_symbolizer() > markers_sym;


    };
}



