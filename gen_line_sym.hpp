
BOOST_FUSION_ADAPT_ADT(
    mapnik::line_symbolizer,
    (mapnik::stroke const&, mapnik::stroke const&, obj.get_stroke(), /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct line_sym_gen : karma::grammar< Iter, mapnik::line_symbolizer() > {
        line_sym_gen() : line_sym_gen::base_type(line_sym) {
            
            using karma::double_;
            using karma::string;
            
            stroke =     ("line-width: "     << double_ << ";\n")
                     << -("line-color: "     << color   << ";\n")
                     << -("line-opacity: "   << double_ << ";\n")
                     << -("line-join: "      << string  << ";\n")
                     << -("line-cap: "       << string  << ";\n")
                     << -("line-gamma: "     << double_ << ";\n")
                     << -("line-dasharray: " << dashpair % ", " << ";\n");
            
            dashpair = double_ << ", " << double_;
            
            line_sym = stroke;
        }
        
        color_rgb< Iter > color;
        
        karma::rule< Iter, dash_pair() > dashpair;
        
        karma::rule< Iter, mapnik::stroke() > stroke;
        karma::rule< Iter, mapnik::line_symbolizer() > line_sym;
        

    };
}