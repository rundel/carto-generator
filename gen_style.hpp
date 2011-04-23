
namespace cssgen {

    typedef std::map<std::string,mapnik::rules > style_map;
    typedef std::pair<std::string,mapnik::rules > style_pair;

}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::style_pair,
    (std::string, first)
    (mapnik::rules, second)
);


BOOST_FUSION_ADAPT_ADT(
    mapnik::rule,
    //(boost::optional<std::string> const&, boost::optional<std::string> const&, obj.get_name_opt(), /**/)
    //(boost::optional<std::string> const&, boost::optional<std::string> const&, mapnik::to_expression_string(*obj.get_filter()), /**/)
    //(boost::optional<std::string> const&, boost::optional<std::string> const&, obj.get_title_opt(), /**/)
    //(boost::optional<std::string> const&, boost::optional<std::string> const&, obj.get_abstract_opt(), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_name(),mapnik::rule().get_name()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(mapnik::to_expression_string(*obj.get_filter()),
                                   mapnik::to_expression_string(*mapnik::rule().get_filter()) ),/**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_title(),mapnik::rule().get_title()), /**/)
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_abstract(),mapnik::rule().get_abstract()) , /**/)
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_min_scale(),mapnik::rule().get_min_scale()) , /**/)    
    (boost::optional<double>, boost::optional<double>, \
     cssgen::make_opt<double>(obj.get_max_scale(),mapnik::rule().get_max_scale()) , /**/)
    //(bool,   bool,   obj.has_else_filter(), /**/)
    (mapnik::rule::symbolizers const&, mapnik::rule::symbolizers const&,  obj.get_symbolizers(), /**/)
);



//BOOST_FUSION_ADAPT_STRUCT(
//    mapnik::rule,
//    (boost::optional<std::string>, get_name_opt())
//    //(boost::optional<std::string>, get_filter_string())
//    (boost::optional<std::string>, get_title_opt())
//    (boost::optional<std::string>, get_abstract_opt())
//    (boost::optional<double>,      get_min_scale_opt())
//    (boost::optional<double>,      get_max_scale_opt())
//    //(bool,   bool,   obj.has_else_filter(), /**/)
//    //(mapnik::symbolizers, syms_)
//);


namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct style_css_gen : karma::grammar< Iter, style_map() > {
        style_css_gen() : style_css_gen::base_type(styles) {
        
            using karma::omit;
            using karma::string;
            using karma::double_;
            using karma::bool_;
            
            symbolizer = poly_sym | line_sym | text_sym;
            
            rule  =    -("::" << string << " ")
                    << -("[" << string << "] ")
                    << "{\n"
                    << -("title: " << qstring << ";\n")
                    << -("abstract: " << qstring << ";\n")
                    << -("min_scale: " << double_ << ";\n")
                    << -("max_scale: " << double_ << ";\n")
                    //<< -("else_filter: " << bool_ << ";\n")
                    << symbolizer % ""
                    
                    << "}";
                          
            rules  = rule % "\n";
            style  =    "::" << string << " {\n"
                     << rules << "\n"
                     << "}";
            styles = style % "\n";
        }

        quoted_string< Iter > qstring;
        line_sym_gen< Iter > line_sym;
        poly_sym_gen< Iter > poly_sym;
        poly_sym_gen< Iter > text_sym;
        

        karma::rule< Iter, style_map() >  styles;
        karma::rule< Iter, style_pair() > style;
        karma::rule< Iter, mapnik::rules() > rules;
        karma::rule< Iter, mapnik::rule() > rule;
        karma::rule< Iter, mapnik::symbolizer() > symbolizer;
    };
}