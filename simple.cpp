#include <iostream>
#include <vector>
#include <map>
#include <utility>

#include <boost/mpl/print.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/fusion/include/std_pair.hpp> 
#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/container/map.hpp> 
#include <boost/variant/recursive_variant.hpp>

namespace karma = boost::spirit::karma;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;



namespace json {

    struct keyval;
    struct object;
    struct array;

    typedef boost::variant< 
        boost::recursive_wrapper<object>, 
        boost::recursive_wrapper<array>, 
        std::string, double, int, bool > value;

    struct keyval : std::pair< std::string, value > {};
    struct object : std::map< std::string, value> {};
    struct array : std::vector<value>{};
}

BOOST_FUSION_ADAPT_STRUCT(
    json::keyval,
    (std::string, first)
    (json::value, second)
);

namespace json {
    
    template< typename Iter > 
    struct json_grammar : qi::grammar< Iter, value(), ascii::space_type > {
        
        json_grammar() : json_grammar::base_type(start) {
            
            using qi::lit;
            using qi::lexeme;
            using qi::double_;
            using qi::int_;
            using qi::bool_;
            using ascii::char_;
            
            quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];
            object_rule   = lit('{') >> pair_rule % ',' >> '}';
            pair_rule     = quoted_string >> ':' >> value_rule;
            array_rule    = lit('[') >> value_rule % ',' >> ']';
            value_rule    = object_rule | array_rule | quoted_string | double_ | int_ | bool_ ;
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

int main(int argc, char **argv) {
    
    using namespace std;
    
    string text( "{\"test\" : 123, \"test2\": {\"key\" : \"hello\"}}"); 

    json::json_grammar< string::const_iterator > parse_grammar;
    json::value json_tree;

    string::const_iterator beg = text.begin();
    string::const_iterator end = text.end();
    bool r = qi::phrase_parse(beg, end, parse_grammar, ascii::space, json_tree);
    
    if (!r) {
        cout << "-------------------------\n";
        cout << "Parse Failed!\n";
        cout << "-------------------------\n";
        return(1); 
    }
    cout << "-------------------------\n";
    cout << "Parse Succeeded!\n";
    cout << "-------------------------\n";
    
    return(0);
}
