#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    private:
        unsigned x_;
        unsigned y_;
         
    public:
        box()
          : x_(123),
            y_(456) {}
            
        unsigned x() const {return x_;}
        unsigned y() const {return y_;}
        
        
        void set_x(unsigned x) {x_=x;}
        void set_y(unsigned y) {y_=y;}
};

BOOST_FUSION_ADAPT_ADT(
    box,
    (unsigned, unsigned,    obj.x(), obj.set_x(val) )
    (unsigned, unsigned,    obj.x(), obj.set_x(val) )
    (unsigned, unsigned,    obj.y(), obj.set_y(val) )
    (unsigned, unsigned,    obj.y(), obj.set_y(val) )
);

int main ( int argc , char** argv) {    
 
    box m;
    typedef std::back_insert_iterator<std::string> iter;
    std::string generated;
    iter sink(generated);
        
    boost::spirit::karma::generate(sink,
        
        (
             ("x:" << boost::spirit::karma::uint_generator<unsigned,10>() << "\n")
          << ("x:" << boost::spirit::karma::uint_generator<unsigned,16>() << "\n")
          << ("y:" << boost::spirit::karma::uint_generator<unsigned,10>() << "\n") 
          << ("y:" << boost::spirit::karma::uint_generator<unsigned,16>() << "\n")
        ),
        m
    );
    std::cout << generated << "\n";
       
}
