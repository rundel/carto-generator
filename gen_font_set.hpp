
namespace cssgen {

    struct font_set_data {
        std::string name_;
        std::vector<std::string> face_names_;

        font_set_data(mapnik::font_set const& rhs) {
            name_ = rhs.get_name();
            face_names_ = rhs.get_face_names();
        }
    };

    typedef std::map<std::string,font_set_data> font_set_map;
    typedef std::pair<std::string,font_set_data> font_set_pair;

}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::font_set_data,
    (std::string, name_)
    (std::vector<std::string>, face_names_)
);

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::font_set_pair,
    (std::string, first)
    (cssgen::font_set_data, second)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    

    template <typename Iter>
    struct font_set_css_gen : karma::grammar< Iter, font_set_map() > {
        font_set_css_gen() : font_set_css_gen::base_type(fs_map) {
        
            using karma::string;
            using karma::omit;
            
            fs_data = omit[string] << qstring % ", " << ";";
            fs_pair = "@" << string << ": " << fs_data;
            fs_map  = fs_pair % "\n" << "\n";
        }

        quoted_string< Iter > qstring;
        
        karma::rule< Iter, font_set_map() > fs_map;
        karma::rule< Iter, font_set_pair() > fs_pair;
        karma::rule< Iter, font_set_data() > fs_data;
    };
}