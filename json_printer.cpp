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
        std::string, double, bool > value;

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
    
    
    ///////////////////////////////////////////////////////////////////////////
    //  Print out the json tree
    ///////////////////////////////////////////////////////////////////////////
    int const tabsize = 4;

    void tab(int indent) {
        for (int i = 0; i < indent; ++i) std::cout << ' ';
    }

    struct json_printer {
        
        json_printer(int indent = 0) : indent(indent) {}
        void operator()(value const& val) const;

        int indent;
    };

    struct json_object_printer {
        
        json_object_printer(int indent = 0) : indent(indent) {}
        void operator()(object const& obj) const;

        int indent;
    };

    struct json_array_printer {
        
        json_array_printer(int indent = 0) : indent(indent) {}
        void operator()(array const& arr) const;

        int indent;
    };

    struct json_value_printer : boost::static_visitor<> {
        
        json_value_printer(int indent = 0) : indent(indent) {
        }

        void operator()(object const& obj) const {
            json_object_printer printer(indent);
            printer(obj);
        }

        void operator()(array const& arr) const {
            json_array_printer printer(indent);
            printer(arr);
        }

        void operator()(std::string const& text) const {
            std::cout << '"' << text << '"';
        }

        void operator()(double const& d) const {
            std::cout << d;
        }
        
        void operator()(bool const& b) const {
            if (b) {
                std::cout << "true";
            } else {
                std::cout << "false";
            }
        }

        int indent;
    };


    void json_printer::operator()(value const& val) const {
        boost::apply_visitor(json_value_printer(indent), val);
        std::cout << std::endl;
    }

    void json_object_printer::operator()(object const& obj) const {
        
        std::cout << '{' << std::endl;

        int curindent = indent + tabsize;

        /*BOOST_FOREACH(TDkeyval const& node, obj) {
            tab(curindent);
            std::cout << '"' << node.first << "\" : ";
            boost::apply_visitor(json_value_printer(curindent), node.second);
            std::cout << "," << std::endl;
        }*/
        
        
        object::const_iterator last = --obj.end();
        
        for(object::const_iterator iter = obj.begin(); iter != obj.end(); ++iter) {
            tab(curindent);
            std::cout << '"' << iter->first << "\" : ";
            boost::apply_visitor(json_value_printer(curindent), iter->second);
            
            if (iter != last)
                std::cout << ",";
            
            std::cout << std::endl;
        }
        
        
        
        tab(indent);
        std::cout << '}';
    }
    
    void json_array_printer::operator()(array const& arr) const {
        
        std::cout << "[ " << std::endl;

        /*BOOST_FOREACH(value const& val, arr) {
            boost::apply_visitor(json_value_printer(indent), val);
            std::cout << "," << std::endl;
        }*/
        
        int curindent = indent + tabsize;
                
        array::const_iterator last = --arr.end();
        
        for(array::const_iterator iter = arr.begin(); iter != arr.end(); ++iter) {
            tab(curindent);
            boost::apply_visitor(json_value_printer(curindent), *iter);
            
            if (iter != last)
                std::cout << ",";
            
            std::cout << std::endl;
        }


        tab(indent);
        std::cout << ']';
    }
    
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
    
    
    json::json_printer printer(0);
    cout << "-------------------------\n";
    cout << "JSON Printer:\n";
    printer(json_tree);
    cout << "-------------------------\n";
    
    
    
    return(0);
}
