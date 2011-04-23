

BOOST_FUSION_ADAPT_ADT(
    mapnik::polygon_symbolizer,
    (boost::optional<mapnik::color>, boost::optional<mapnik::color>, \
     cssgen::make_opt<mapnik::color>(obj.get_fill(),mapnik::polygon_symbolizer().get_fill()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_opacity(),mapnik::polygon_symbolizer().get_opacity()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_gamma(),mapnik::polygon_symbolizer().get_gamma()), /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct poly_sym_gen : karma::grammar< Iter, mapnik::polygon_symbolizer() > {
        poly_sym_gen() : poly_sym_gen::base_type(poly_sym) {
        
            using karma::double_;
        
            poly_sym =    -("polygon-fill: "     << color   << ";\n")
                       << -("polygon-opacity: "   << double_ << ";\n")
                       << -("polygon-gamma: "     << double_ << ";\n");
        
        }
        
        color_hex< Iter > color;
        karma::rule< Iter, mapnik::polygon_symbolizer() > poly_sym;

    };
}