#include "gen_utility.hpp"

namespace cssgen {

template <typename Iter>
quoted_string<Iter>::quoted_string() : quoted_string::base_type(str) {
    
    using karma::string;
    
    str = "\"" << string << "\"";
}

template <typename Iter>
color_hex<Iter>::color_hex() : color_hex::base_type(c) {

    using karma::hex;
    using karma::true_;
    using karma::bool_;
    using karma::omit;
    
    c = "#" << ( hex << hex << hex << &true_ << hex
               | hex << hex << hex << omit[bool_] << omit[hex]);
}

template <typename Iter>
color_rgb<Iter>::color_rgb() : color_rgb::base_type(c) {
    
    using karma::uint_;
    using karma::true_;
    using karma::bool_;
    using karma::omit;
    
    c = "rgb(" << ( uint_ << ", " << uint_ << ", " << uint_ << &true_ << ", " << uint_
                  | uint_ << ", " << uint_ << ", " << uint_ << omit[bool_] << omit[uint_] )
          << ")";
}

}