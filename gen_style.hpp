
namespace cssgen {

    typedef std::map<std::string,std::vector<rule_data> > style_map;
    typedef std::pair<std::string,std::vector<rule_data> > style_pair;

}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::style_pair,
    (std::string, first)
    (std::vector<cssgen::rule_data>, second)
);

/*namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct style_css_gen : karma::grammar< Iter, style_map() > {
        style_css_gen() : style_css_gen::base_type(styles) {
        
            using karma::string;
            using karma::double_;
            using karma::bool_;
            
            style_rule  =    -("name: " <<  string)
                          << -("title: " << string)
                          << -("abstract: " << string)
                          << -("min_scale: " << double_)
                          << -("max_scale: " << double_)
                          << -("else_filter: " << bool_);
                          
            style_rules = style_rule % ", ";
            style       = string << style_rules;
            styles      = style % ",\n                    ";
        }

        karma::rule< Iter, style_map() >  styles;
        karma::rule< Iter, style_pair() > style;
        karma::rule< Iter, std::vector<rule_data>() > style_rules;
        karme::rule< Iter, rule_data() > style_rule;
    };
}*/