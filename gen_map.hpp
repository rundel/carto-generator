
namespace cssgen {

struct map_data {       
        std::string  srs_;
        boost::optional<mapnik::color> background_;
        boost::optional<std::string> background_image_;
        boost::optional<int> buffer_size_;
        
        std::vector<layer_data> layers_; 

        boost::optional<font_set_map> fontsets_;
        
        //styles_(rhs.styles_),
        //metawriters_(rhs.metawriters_),
        //parameters extra_attr_;

        map_data() {}
        
        map_data(const mapnik::Map& rhs) {
            srs_ = rhs.srs();
            background_image_ = rhs.background_image();
            background_ = rhs.background();
            
            if (rhs.buffer_size() != mapnik::Map().buffer_size())
                buffer_size_ = rhs.buffer_size();

            
            BOOST_FOREACH(mapnik::layer const& lyr, rhs.layers()) {

                layer_data ld(lyr);
                
                std::map<std::string, mapnik::feature_type_style> fts_map = rhs.styles();
                   
                BOOST_FOREACH(std::string const& style_name, lyr.styles()) {
                    ld.styles_[style_name] = fts_map[style_name].get_rules();
                }
                    
                layers_.push_back(ld);

            }
            
            if (!rhs.fontsets().empty())  {
                fontsets_ = rhs.fontsets();
            }
            

        }
};
}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::map_data,
    (boost::optional<cssgen::font_set_map>, fontsets_)
    (std::string, srs_ )
    (boost::optional<std::string>, background_image_ )
    (boost::optional<mapnik::color>, background_ )
    (boost::optional<int>, buffer_size_ )
    (std::vector<cssgen::layer_data>, layers_)
);




namespace cssgen {
    
    namespace karma = boost::spirit::karma;
    
    using karma::lit;
    using karma::omit;
    using karma::int_;
    using karma::attr_cast;
    
    template <typename Iter>
    struct mml_gen : karma::grammar< Iter, map_data() > {
        mml_gen() : mml_gen::base_type(mml) {
            
            mml =    omit[-font_sets]
                  << "{\n"
                  << "\"srs\": " << qstring << ",\n"
                  << omit[qstring]
                  << omit[bg_hex]
                  << omit[-int_]
                  << "\"Stylesheet\": [\n"
                  << "\"style.mss\"\n"
                  << "],\n"
                  << "\"Layer\": [\n" 
                  << ("{\n" << layer << "}") % ",\n" << "\n"
                  << "]\n"
                  << "}";
        }
        
        quoted_string< Iter > qstring;
        color_hex< Iter > bg_hex;
        
        layer_mml_gen< Iter > layer;
        font_set_css_gen< Iter > font_sets;
    
        karma::rule< Iter, map_data() > mml;
    };   


    template <typename Iter>
    struct mss_gen : karma::grammar< Iter, map_data() > {
        mss_gen() : mss_gen::base_type(mms) {
            
            mms =    -font_sets
                  << "\n"
                  << "Map {\n"
                  << "srs: " << qstring << ";\n"
                  << -("background-image: " << qstring << ";\n")
                  << -("background-color: " << bg_hex << ";\n")
                  << -("buffer-size: " << int_ << ";\n")
                  << "}\n"
                  << "\n"
                  << layer % "\n";
        }
        
        quoted_string< Iter > qstring;
        color_hex< Iter > bg_hex;
        
        layer_mss_gen< Iter > layer;
        font_set_css_gen< Iter > font_sets;
    
        karma::rule< Iter, map_data() > mms;
        
    };

}