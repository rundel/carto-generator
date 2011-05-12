
    
BOOST_FUSION_ADAPT_ADT(
    mapnik::color,
    (unsigned, unsigned, obj.red(),   /**/)
    (unsigned, unsigned, obj.green(), /**/)
    (unsigned, unsigned, obj.blue(),  /**/)
    (bool,     bool,     obj.alpha()!=255, /**/)
    (unsigned, unsigned, obj.alpha(), /**/)
)


namespace cssgen {
    
    template <class T> 
    boost::optional<T> make_opt(T val, T dfl_val)
    {
        if (val == dfl_val)
            return boost::optional<T>();

        return boost::optional<T>(val);
    }
    
    template <class T> 
    boost::optional<T> make_opt_has(T val, bool has)
    {
        if (!has)
            return boost::optional<T>();

        return boost::optional<T>(val);
    }
    
    template <class T> 
    boost::optional<T> make_opt_empty(T val)
    {
        if (val.empty())
            return boost::optional<T>();

        return boost::optional<T>(val);
    }
    
    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct quoted_string : karma::grammar< Iter, std::string() > {
        quoted_string() : quoted_string::base_type(str) {
            str = "\"" << karma::string << "\"";
        }
        karma::rule< Iter, std::string() > str;
    };

    template <typename Iter>
    struct color_hex : karma::grammar< Iter, mapnik::color() > {
        color_hex() : color_hex::base_type(c) {
            
            using karma::hex;
            using karma::true_;
            using karma::bool_;
            using karma::omit;
            
            c = "#" << ( hex << hex << hex << &true_ << hex
                       | hex << hex << hex << omit[bool_] << omit[hex]);
        }
        karma::rule< Iter, mapnik::color() > c;
    };

    template <typename Iter>
    struct color_rgb : karma::grammar< Iter, mapnik::color() > {
        color_rgb() : color_rgb::base_type(c) {
            
            using karma::uint_;
            using karma::true_;
            using karma::bool_;
            using karma::omit;
            
            c = "rgb(" << ( uint_ << ", " << uint_ << ", " << uint_ << &true_ << ", " << uint_
                          | uint_ << ", " << uint_ << ", " << uint_ << omit[bool_] << omit[uint_] )
                  << ")";
        }
        karma::rule< Iter, mapnik::color() > c;
    };
}