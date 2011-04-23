namespace cssgen {

namespace karma = boost::spirit::karma;

struct linecap_ : karma::symbols<int,char const*>
{
    linecap_()
    {
        add(0, "butt")
           (1, "square")
           (2, "round");
    }
};

struct linejoin_ : karma::symbols<int,char const*>
{
    linejoin_()
    {
        add(0, "miter")
           (1, "miter_revert")
           (2, "round")
           (3, "bevel");
    }
};

typedef std::pair<double,double> dash_pair;
}

BOOST_FUSION_ADAPT_ADT(
    mapnik::line_symbolizer,
    (mapnik::stroke const&, mapnik::stroke const&, obj.get_stroke(), /**/)
);

BOOST_FUSION_ADAPT_ADT(
    mapnik::stroke,
    (boost::optional<mapnik::color>, boost::optional<mapnik::color>, \
     cssgen::make_opt<mapnik::color>(obj.get_color(),mapnik::stroke().get_color()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_width(),mapnik::stroke().get_width()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_opacity(),mapnik::stroke().get_opacity()), /**/)
    (boost::optional<int>, boost::optional<int>, \
     cssgen::make_opt<int>(obj.get_line_join(),mapnik::stroke().get_line_join()), /**/)
    (boost::optional<int>, boost::optional<int>, \
     cssgen::make_opt<int>(obj.get_line_cap(),mapnik::stroke().get_line_cap()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_gamma(),mapnik::stroke().get_gamma()), /**/)
    (boost::optional<mapnik::dash_array>, boost::optional<mapnik::dash_array>, \
     cssgen::make_opt_has<mapnik::dash_array>(obj.get_dash_array(),obj.has_dash()), /**/)
);

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::dash_pair,
    (double, first)
    (double, second)
);


namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct line_sym_gen : karma::grammar< Iter, mapnik::line_symbolizer() > {
        line_sym_gen() : line_sym_gen::base_type(line_sym) {
            
            using karma::double_;
            
            stroke =    -("line-color: "     << color    << ";\n")
                     << -("line-width: "     << double_  << ";\n")
                     << -("line-opacity: "   << double_  << ";\n")
                     << -("line-join: "      << linejoin << ";\n")
                     << -("line-cap: "       << linecap  << ";\n")
                     << -("line-gamma: "     << double_  << ";\n")
                     << -("line-dasharray: " << dashpair % "," << ";\n");
            
            dashpair = double_ << ", " << double_;
            
            line_sym = stroke;
        }
        
        linecap_ linecap;
        linejoin_ linejoin;
        
        color_hex< Iter > color;
        
        karma::rule< Iter, dash_pair() > dashpair;
        
        karma::rule< Iter, mapnik::stroke() > stroke;
        karma::rule< Iter, mapnik::line_symbolizer() > line_sym;
        

    };
}