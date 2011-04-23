#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/assert.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

template <typename P>
void test_parser(
    char const* input, P const& p, bool full_match = true)
{
    using boost::spirit::qi::parse;

    char const* f(input);
    char const* l(f + strlen(f));
    if (parse(f, l, p) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}


int main ( int argc , char** argv) {    
    using boost::phoenix::val;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::uint_;
    using boost::spirit::qi::uint_parser;

    // unsigned int
    test_parser("12345", uint_);
    //test_parser("12345", uint_(12345)); 
    //test_parser("12345", uint_(val(12345)));

    // literals
    //test_parser("12345", lit(12345)); 
    //test_parser("12345", lit(val(12345)));
    //
    //uint_parser<unsigned, 10, 1, 3> uint3_p;        //  1..3 digits
    //uint_parser<unsigned, 10, 3, 3> uint3_3_p;      //  exactly 3 digits        
    //test_parser("12,345,678", uint3_p >> *(',' >> uint3_3_p));   
}
