
namespace cssgen {
    
    namespace karma = boost::spirit::karma;
    
    //template <typename Iter> karma::rule< Iter, std::string() > qstring = "\"" << karma::string << "\"";    

    template <typename Iter>
    struct quoted_string : karma::grammar< Iter, std::string() > {
        quoted_string() : quoted_string::base_type(str) {
            str = "\"" << karma::string << "\"";
        }
        karma::rule< Iter, std::string() > str;
    };



    template <typename Iter>
    struct color_hex : karma::grammar< Iter, mapnik::css() > {
        color_hex() : color_hex::base_type(css) {
            using karma::hex;
            css = "#" << hex << hex << hex << -hex;
        }
        karma::rule< Iter, mapnik::css() > css;
    };


    template <typename Iter>
    struct color_rgb : karma::grammar< Iter, mapnik::css() > {
        color_rgb() : color_rgb::base_type(css) {
            using karma::uint_;
            css = "rgb(" << uint_ 
                         << ", " << uint_ 
                         << ", " << uint_ 
                         << -(", " << uint_) 
                         << ")";
        }
        karma::rule< Iter, mapnik::css() > css;
    };
}