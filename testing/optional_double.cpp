#include <boost/optional.hpp>

#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {
    public:
        boost::optional<double> a_;
        boost::optional<double> b_;
        
        boost::optional<double> const& a() const {return a_;}
        boost::optional<double> const& b() const {return b_;}
};


BOOST_FUSION_ADAPT_ADT(
    box,
    (boost::optional<double> const&, boost::optional<double> const&, obj.a(), /**/ )
    (boost::optional<double> const&, boost::optional<double> const&, obj.b(), /**/ )
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
          << -("a: " << boost::spirit::karma::double_ << "\n")
          << -("b: " << boost::spirit::karma::double_ << "\n")
        ),
        m
    );

    std::cout << generated;
       
}
