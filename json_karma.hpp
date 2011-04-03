#include <boost/spirit/include/karma.hpp>

namespace json {
    
    namespace karma = boost::spirit::karma;
    namespace ascii = boost::spirit::ascii;
    
    template <typename Iter>
    struct json_gen_grammar : karma::grammar< Iter, value() > {
        json_gen_grammar() : json_gen_grammar::base_type(start) {
            
            using karma::double_;
            using karma::bool_;
            using ascii::char_;
            
            value_rule    = object_rule | array_rule | quoted_string | double_ | bool_ ;
            quoted_string = '"' << +char_ << '"';
            pair_rule     = quoted_string << " : " << value_rule;
            object_rule   = "{\n" << pair_rule % ",\n" << "\n}";
            array_rule    = "[\n" << value_rule % ",\n" << "\n]";
            start         = value_rule;
        }

        karma::rule< Iter, value()       > start;
        karma::rule< Iter, std::string() > quoted_string;
        karma::rule< Iter, value()       > value_rule;
        karma::rule< Iter, object()      > object_rule;
        karma::rule< Iter, TDkeyval()    > pair_rule;
        karma::rule< Iter, array()       > array_rule;
    };
    
}