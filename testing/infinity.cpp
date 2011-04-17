#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    public:
        double data_;
        box(double data=0.0)
         : data_( data ) {}   
        
        double data() const { return data_;}
        void set_data(double data) { data_=data;}
};

BOOST_FUSION_ADAPT_ADT(
    box,
    (double, double, obj.data(), obj.set_data(val) )
);

/*BOOST_FUSION_ADAPT_STRUCT(
    box,
    (double,data_)
);*/

void test(box& x) {
    std::cout << "Testing        : x=" << x.data() << std::endl;
    
    typedef std::back_insert_iterator<std::string> iter;
    
    
    std::string generated;
    iter sink = iter(generated);
    
    boost::spirit::karma::generate(sink,
        ( "x=" << boost::spirit::karma::double_),
        x.data()
    );
    std::cout << "Karma          : " << generated << std::endl;
    
    
    generated = "";
    sink = iter(generated);
    
    boost::spirit::karma::generate(sink,
        ( "x=" << boost::spirit::karma::double_),
        x
    );
    std::cout << "Karma+FusionADT: " << generated << std::endl;
    
    std::cout << std::endl;
}


int main ( int argc , char** argv) {    
 
    box x0 = box(),
        x1 = box(1.1), 
        x2 = box(1e10), 
        x3 = box(std::numeric_limits<double>::min()),
        x4 = box(std::numeric_limits<double>::max()),
        x5 = box(std::numeric_limits<double>::infinity()),
        x6 = box(std::numeric_limits<double>::quiet_NaN()),
        x7 = box(std::numeric_limits<double>::signaling_NaN());
        
    
    test(x0);
    test(x1);
    test(x2);
    test(x3);
    test(x4);
    test(x5);
    test(x6);
    test(x7);
}