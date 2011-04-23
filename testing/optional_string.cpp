#include <boost/optional.hpp>

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    public:
        boost::optional<std::string> a_;
        boost::optional<std::string> b_;
                        
        boost::optional<std::string> a() const {return a_;}
        boost::optional<std::string> b() const {return b_;}
};


BOOST_FUSION_ADAPT_ADT(
    box,
    (boost::optional<std::string>, boost::optional<std::string>, obj.a(), /**/ )
    (boost::optional<std::string>, boost::optional<std::string>, obj.b(), /**/ )
);


int main ( int argc , char** argv) {    
 
    box m;

    m.a_="hello";
    
    std::string generated;
    std::back_insert_iterator<std::string> sink(generated);

    boost::spirit::karma::generate(sink,
        ( boost::spirit::karma::lit("Testing:\n")
          << -("a: " << boost::spirit::karma::string << "\n")
          << -("b: " << boost::spirit::karma::string << "\n")
        ),
        m
    );

    std::cout << generated;
       
}
