#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/include/adapt_struct_named.hpp> 

#include <boost/spirit/include/karma.hpp>
//#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

struct B {       
    int m;
    int n;
    B(int i, int j) : m(i), n(j) {}
};

struct A {       
    std::vector<B> x;
    std::string y;
};


BOOST_FUSION_ADAPT_STRUCT(
    A,
    (std::string, y)
    (std::vector<B>, x)
);

BOOST_FUSION_ADAPT_STRUCT(
    B,
    (int, m)
    (int, n)
);

BOOST_FUSION_ADAPT_STRUCT_NAMED(
    B, Bn,
    (int, n)
);


namespace karma = boost::spirit::karma;

using karma::string;
using karma::int_;


template <typename Iter>
struct B_grammar : karma::grammar< Iter, A() > {
    B_grammar() : B_grammar::base_type(A_rule) {
        
        B_rule = int_ << ", " << int_;
        A_rule =    string << ": \n" 
                 << B_rule % "\n";
    }
    
    karma::rule< Iter, B() > B_rule;
    karma::rule< Iter, A() > A_rule;
    
};


template <typename Iter>
struct Bn_grammar : karma::grammar< Iter, A() > {
    Bn_grammar() : Bn_grammar::base_type(A_rule) {
        
        Bn_rule = int_;
        A_rule =    string << ": \n" 
                 << Bn_rule % "\n";
    }
    
    karma::rule< Iter, boost::fusion::adapted::Bn() > Bn_rule;
    karma::rule< Iter, A() > A_rule;
    
};


int main ( int argc , char** argv) {    
 
    A data;
    data.x.push_back(B(1,2));
    data.x.push_back(B(3,4));
    data.x.push_back(B(5,6));
    data.x.push_back(B(7,8));
    
    data.y = "testing";
    
    typedef std::back_insert_iterator<std::string> iter;
    
    std::string generated;
    iter sink(generated);
    
    //B_grammar< iter > g;
    Bn_grammar< iter > g;
            
    bool r=karma::generate(sink, g, data);
    
    if (r) {
        std::cout << generated << "\n";
    }
      
}
