
namespace cssgen {

struct map_data {       
        std::string  srs_;
        boost::optional<mapnik::css> background_;
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
            
            if (rhs.buffer_size() != mapnik::Map().buffer_size())
                buffer_size_ = rhs.buffer_size();
            
            if (rhs.background()) {
                mapnik::color tmp = *(rhs.background());
                background_ = mapnik::css(tmp.red(),tmp.green(),tmp.blue(),tmp.alpha());
            }
            
            BOOST_FOREACH(mapnik::layer const& lyr, rhs.layers()) {

                layer_data tmp(lyr);
                
                std::map<std::string, mapnik::feature_type_style> fts_map = rhs.styles();
                   
                BOOST_FOREACH(std::string const& style_name, lyr.styles()) {
                    
                    tmp.styles_[style_name] = std::vector<rule_data>(); 
                    
                    BOOST_FOREACH(mapnik::rule r, fts_map[style_name].get_rules() ) {
                        tmp.styles_[style_name].push_back(rule_data(r));
                    }

                }
                    
                layers_.push_back(tmp);

            }
            
            if (!rhs.fontsets().empty())  {
                
                fontsets_ = font_set_map();
                
                std::pair<std::string,mapnik::font_set> fs;
                BOOST_FOREACH( fs, rhs.fontsets()) {
                    
                    (*fontsets_).insert(font_set_pair(fs.first, font_set_data(fs.second)));
                }
            }
            

        }
};
}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::map_data,
    (boost::optional<cssgen::font_set_map>, fontsets_)
    (std::string, srs_ )
    (boost::optional<std::string>, background_image_ )
    (boost::optional<mapnik::css>, background_ )
    (boost::optional<int>, buffer_size_ )
    (std::vector<cssgen::layer_data>, layers_)
);

/*BOOST_FUSION_ADAPT_ADT(
    mapnik::Map,
    (std::string const&, std::string const&, obj.srs(), obj.set_srs(val) )
    (unsigned, unsigned, obj.width(),  obj.set_width(val) )
    (unsigned, unsigned, obj.height(), obj.set_height(val) )
    (boost::optional<std::string> const&, boost::optional<std::string> const&, obj.background_image(), obj.set_background_image(val) )
    //(boost::optional<mapnik::color> const&, mapnik::color const&, obj.background(), obj.set_background(val) )
    //(mapnik::parameters, mapnik::parameters, obj.get_extra_attributes(), obj.set_extra_attributes(val))
) ;*/


namespace cssgen {
    
    namespace karma = boost::spirit::karma;
    
    using karma::lit;
    using karma::omit;
    using karma::int_;
    
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
        
        layer_css_gen< Iter > layer;
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
                  << omit [layer % ""];
        }
        
        quoted_string< Iter > qstring;
        color_hex< Iter > bg_hex;
        
        layer_css_gen< Iter > layer;
        font_set_css_gen< Iter > font_sets;
    
        karma::rule< Iter, map_data() > mms;
        
    };



    template <typename Iter>
    struct map_css_gen : karma::grammar< Iter, map_data() > {
        map_css_gen() : map_css_gen::base_type(map) {
            
            using karma::string;

            map =     ("srs               : " << string << "\n") 
                  << -("background_image  : " << string << "\n")
                  << -("background        : " << bg_dec)
                  << -("Fontsets          : " << font_sets)
                  <<  ("Layer : \n" << layer) % "\n";
        }
        
        
        karma::rule< Iter, map_data() > map;
        color_hex< Iter > bg_hex;
        color_rgb< Iter > bg_dec;
        layer_css_gen< Iter > layer;
        font_set_css_gen< Iter > font_sets;
    };   
}