#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    private:
        std::string data_;
         
    public:
        box() : data_("test") {}   
        std::string data() const { return data_;}
        void set_data(std::string data) { data_=data;}
};

BOOST_FUSION_ADAPT_ADT(
    box,
    (std::string, std::string, obj.data(), obj.set_data(val) )
);

int main ( int argc , char** argv) {    
 
    box m;
    
    std::string css_generated;
    std::back_insert_iterator<std::string> sink(css_generated);

    std::cout << "data: " << m.data() << "\n";
    std::cout << "\n";
    
        
    bool r=boost::spirit::karma::generate(sink,
        
        // Both of the following rules produce compiler errors
        
        ( "data: " << boost::spirit::karma::string << "\n"),
        //( "data: " << +boost::spirit::karma::char_ << "\n"),
        m
    );
    
    if (!r) {
       std::cout << "-------------------------\n";
       std::cout << "Generating Failed!\n";
       std::cout << "-------------------------\n";
       return(1); 
    }
    std::cout << "-------------------------\n";
    std::cout << "Generated:\n" << css_generated;
    std::cout << "-------------------------\n";
       
}
