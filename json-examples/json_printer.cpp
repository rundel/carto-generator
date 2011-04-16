#include <iostream>
#include <fstream>
#include <sstream>

#include "json.hpp"
#include "json_parser.hpp"
#include "json_printer.hpp"

int main(int argc, char **argv) {
    
    using namespace std;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
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
