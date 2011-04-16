#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/support_adapt_adt_attributes.hpp>

#include <iostream>

class box {       
    private:
        std::string data_;
        int x_;
        double y_;
        bool z_;
         
    public:
        box()
          : data_("test"),
            x_(123),
            y_(456.7),
            z_(false) {}   
        
        std::string data() const { return data_;}
        int x() const {return x_;}
        double y() const {return y_;}
        bool z() const {return z_;}
        
        void set_data(std::string data) { data_=data;}
        void set_x(int x) {x_=x;}
        void set_y(double y) {y_=y;}
        void set_z(bool z) {z_=z;}
        
};

BOOST_FUSION_ADAPT_ADT(
    box,
    (std::string, std::string, obj.data(), obj.set_data(val) )
    (std::string, std::string, obj.data(), obj.set_data(val) )
    (int,    int,    obj.x(), obj.set_x(val) )
    (double, double, obj.y(), obj.set_y(val) )
    (bool,   bool,   obj.z(), obj.set_z(val) )
);

int main ( int argc , char** argv) {    
 
    box m;
    
    std::string css_generated;
    std::back_insert_iterator<std::string> sink(css_generated);

    std::cout << "data: " << m.data() << "\n";
    std::cout << "x: " << m.x() << "\n";
    std::cout << "y: " << m.y() << "\n";
    std::cout << "z: " << m.z() << "\n";
    
    std::cout << "\n";
    
        
    bool r=boost::spirit::karma::generate(sink,
        
        (
             ("data(string): " << boost::spirit::karma::string << "\n")
          << ("data(char): " << +boost::spirit::karma::char_ << "\n")
          << ("x:" << boost::spirit::karma::int_ << "\n")
          << ("y:" << boost::spirit::karma::double_ << "\n")
          << ("z:" << boost::spirit::karma::bool_ << "\n")
        ),
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
