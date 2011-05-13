namespace cssgen {

typedef std::pair<double,double> dash_pair;

}

BOOST_FUSION_ADAPT_ADT(
    mapnik::stroke,
    (double, double, obj.get_width(), /**/)
    (boost::optional<mapnik::color>, boost::optional<mapnik::color>, \
     cssgen::make_opt<mapnik::color>(obj.get_color(),mapnik::stroke().get_color()), /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_opacity(),mapnik::stroke().get_opacity()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_line_join().as_string(),mapnik::stroke().get_line_join().as_string()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_line_cap().as_string(),mapnik::stroke().get_line_cap().as_string()), /**/)
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