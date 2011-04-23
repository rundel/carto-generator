#include <boost/optional.hpp>

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    public:
        boost::optional<int> a_;
        boost::optional<int> b_;
                        
        boost::optional<int> a() const {return a_;}
        boost::optional<int> b() const {return b_;}
};


BOOST_FUSION_ADAPT_ADT(
    box,
    (boost::optional<int>, boost::optional<int>, obj.a(), /**/ )
    (boost::optional<int>, boost::optional<int>, obj.b(), /**/ )
);


//BOOST_FUSION_ADAPT_STRUCT(
//    box,
//    (boost::optional<int>, a_)
//    (boost::optional<int>, b_)
//);

int main ( int argc , char** argv) {    
 
    box m;

    m.a_=10;
    
    std::string generated;
    std::back_insert_iterator<std::string> sink(generated);

    boost::spirit::karma::generate(sink,
        ( boost::spirit::karma::lit("Testing:\n")
          << -("a: " << boost::spirit::karma::int_ << "\n")
          << -("b: " << boost::spirit::karma::int_ << "\n")
        ),
        m
    );

    std::cout << generated;
       
}
