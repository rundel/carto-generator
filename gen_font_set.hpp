
namespace cssgen {

    typedef std::map<std::string,mapnik::font_set> font_set_map;
    typedef std::pair<std::string,mapnik::font_set> font_set_pair;

}

BOOST_FUSION_ADAPT_ADT(
    mapnik::font_set,
    (std::string const&, std::string const&, obj.get_name(), /**/ )
    (std::vector<std::string> const&, std::vector<std::string> const&, obj.get_face_names(), /**/)
);

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::font_set_pair,
    (std::string, first)
    (mapnik::font_set, second)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    using karma::string;
    using karma::omit;

    template <typename Iter>
    struct font_set_css_gen : karma::grammar< Iter, font_set_map() > {
        font_set_css_gen() : font_set_css_gen::base_type(fs_map) {
            
            fs = omit[string] << qstring % ", " << ";";
            fs_pair = "@" << string << ": " << fs;
            fs_map  = fs_pair % "\n" << "\n";
        }

        quoted_string< Iter > qstring;
        
        karma::rule< Iter, font_set_map() > fs_map;
        karma::rule< Iter, font_set_pair() > fs_pair;
        karma::rule< Iter, mapnik::font_set() > fs;
    };
}