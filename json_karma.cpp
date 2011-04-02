#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
    
    typedef std::pair< std::string, value > TDkeyval;
    
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

int main(int argc, char **argv) {
    
    using namespace std;
    
    cout << endl << "Using Boost version: "
         << (BOOST_VERSION / 100000) << "."
         << (BOOST_VERSION / 100 % 1000) << "."
         << (BOOST_VERSION % 100) << endl << endl;
    
    
    char const* filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        cerr << "Error: No input file provided." << endl;
        return 1;
    }

    ifstream file(filename, ios_base::in);

    if (!file)
    {
        cerr << "Error: Could not open input file: " << filename << endl;
        return 1;
    }
    
    
    string text; // We will read the contents here.
    file.unsetf(ios::skipws); // No white space skipping!
    copy(istream_iterator<char>(file),
         istream_iterator<char>(),
         back_inserter(text));
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
    cout << "-------------------------\n\n";
    
    
    
    string json_generated;
    back_insert_iterator<string> sink(json_generated);
    
    json::json_gen_grammar< back_insert_iterator<string> > json_grammar;
    r = karma::generate(sink, json_grammar, json_tree);

    if (!r) {
        cout << "-------------------------\n";
        cout << "Generating Failed!\n";
        cout << "-------------------------\n";
        return(1); 
    }
    cout << "-------------------------\n";
    cout << "Generated:\n" << json_generated << endl;
    cout << "-------------------------\n";
    
    
    return(0);
}
