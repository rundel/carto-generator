
BOOST_FUSION_ADAPT_STRUCT(
    mapnik::parameter,
    (std::string, first)
    (mapnik::value_holder, second)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct parameter_css_gen : karma::grammar< Iter, mapnik::parameters() > {
        parameter_css_gen() : parameter_css_gen::base_type(param_map) {
        
            using karma::double_;
            using karma::int_;
            using karma::string;
            using karma::lit;
            
            //qstring = "\"" << boost::spirit::karma::string << "\"";
            
            param_value = int_ | double_ | qstring;
            param_pair  = qstring << ": " << param_value;
            param_map   = param_pair % ",\n";
        }
        
        //karma::rule< Iter, std::string() > qstring;
        quoted_string< Iter > qstring;
        karma::rule< Iter, mapnik::parameters() > param_map;
        karma::rule< Iter, mapnik::parameter() > param_pair;
        karma::rule< Iter, mapnik::value_holder() > param_value;
    };
}