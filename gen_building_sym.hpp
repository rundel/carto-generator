
BOOST_FUSION_ADAPT_ADT(
    mapnik::building_symbolizer,
    // building-fill
    (mapnik::color, mapnik::color, obj.get_fill(), /**/)
    // building-fill-opacity
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.get_opacity(),
                              mapnik::building_symbolizer().get_opacity()),
     /**/)
    // building-height
    (boost::optional<double>,
     boost::optional<double>,
     cssgen::make_opt<double>(obj.height(),
                              mapnik::building_symbolizer().height()),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct building_sym_gen : karma::grammar< Iter, mapnik::building_symbolizer() > {
        building_sym_gen() : building_sym_gen::base_type(building_sym) {
        
            using karma::double_;
        
            building_sym =     ("building-fill: "         << color   << ";\n")
                           << -("building-fill-opacity: " << double_ << ";\n")
                           << -("building-height: "       << double_ << ";\n");
        }
        
        color_rgb< Iter > color;
        karma::rule< Iter, mapnik::building_symbolizer() > building_sym;
    };
}
