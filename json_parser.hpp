#include <boost/spirit/include/qi.hpp>

namespace json {
    
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    template< typename Iter > 
    struct json_grammar : qi::grammar< Iter, value(), ascii::space_type > {
    
    
        json_grammar() : json_grammar::base_type(start) {
            
            using qi::lexeme;
            using qi::double_;
            using qi::bool_;
            using ascii::char_;
            
            quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];
            object_rule   = '{' >> pair_rule % ',' >> '}';
            pair_rule     = quoted_string >> ':' >> value_rule;
            array_rule    = '[' >> value_rule % ',' >> ']';
            value_rule    = object_rule | array_rule | quoted_string | double_ | bool_ ;
            start         = value_rule;
        }
    
        qi::rule< Iter, value(),        ascii::space_type > start;
        qi::rule< Iter, std::string(),  ascii::space_type > quoted_string;
        qi::rule< Iter, value(),        ascii::space_type > value_rule;
        qi::rule< Iter, object(),       ascii::space_type > object_rule;
        qi::rule< Iter, keyval(),       ascii::space_type > pair_rule;
        qi::rule< Iter, array(),        ascii::space_type > array_rule;
        
    };
}