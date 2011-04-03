#include <iostream>
#include "json.hpp"
#include "json_parser.hpp"

int main(int argc, char **argv) {
    
    using namespace std;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
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
