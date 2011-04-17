
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
    (std::string const&, std::string const&, obj.get_name(), obj.set_name(val))
    (std::string const&, std::string const&, obj.get_title(), obj.set_title(val))
    (std::string const&, std::string const&, obj.get_abstract(), obj.set_abstract(val))
    (double, double, obj.get_min_scale(), obj.set_min_scale(val))
    (double, double, obj.get_max_scale(), obj.set_max_scale(val))
    (bool,   bool,   obj.has_else_filter(), obj.set_else(val))
    //(mapnik::symbolizers, syms_)
    //(mapnik::expression_ptr, filter_)
);



namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct style_css_gen : karma::grammar< Iter, style_map() > {
        style_css_gen() : style_css_gen::base_type(styles) {
        
            using karma::omit;
            using karma::string;
            using karma::double_;
            using karma::bool_;
            
            rule  =    string << " {\n"
                    << "title: " << qstring << ";\n"
                    << "abstract: " << qstring << ";\n"
                    << "min_scale: " << double_ << ";\n"
                    << "max_scale: " << double_ << ";\n"
                    << "else_filter: " << bool_ << ";\n"
                    << "}\n";
                          
            rules  = rule % "\n";
            style  =    string << " {\n"
                     << rules
                     << "}\n";
            styles = style % "\n";
        }

        quoted_string< Iter > qstring;

        karma::rule< Iter, style_map() >  styles;
        karma::rule< Iter, style_pair() > style;
        karma::rule< Iter, mapnik::rules() > rules;
        karma::rule< Iter, mapnik::rule() > rule;
    };
}