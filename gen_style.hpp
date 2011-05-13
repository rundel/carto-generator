
namespace cssgen {

typedef std::map<std::string,mapnik::rules > style_map;
typedef std::pair<std::string,mapnik::rules > style_pair;

int find_zoom(double denom, bool max) 
{
    const int max_zoom = 22;
    const double zoom_ranges[] = { 1000000000, 500000000, 200000000, 100000000,
                                     50000000,  25000000,  12500000,   6500000,
                                      3000000,   1500000,    750000,    400000,
                                       200000,    100000,     50000,     25000,
                                        12500,      5000,      2500,      1000,
                                          500,       250,       100,        50};

    for(int i = 0; i <= max_zoom; i++) {

        if (zoom_ranges[i] == denom) 
            return i;

        if (zoom_ranges[i] < denom)
            return i-(int)max;
    }
    
    return (max) ? 0 : max_zoom;
}



boost::optional<std::string> conv_zoom(boost::optional<double> scale_min, boost::optional<double> scale_max)
{    
    boost::optional<int> zoom_min, zoom_max;

    if(scale_min)
        zoom_min = find_zoom(*scale_min,false);
    if(scale_max)
        zoom_max = find_zoom(*scale_max,true);

    std::stringstream s;
    if (zoom_min && zoom_max) {
    
        if (*zoom_min-*zoom_max == 1) {
            s << "[zoom = " << *zoom_max << "]";
        } else {
            // FIXME - double check that this is correct
            s << "[zoom <= " << *zoom_min << "]"
              << "[zoom >= " << *zoom_max << "]";
        }
        
    } else if (zoom_min) {
        s << "[zoom < " << *zoom_min+1 << "]";
    } else if (zoom_max) {
        s << "[zoom > " << *zoom_max-1 << "]";
    }
    
    boost::optional<std::string> res;
    if (!s.str().empty())
        res = s.str();
        
    return res;
}


}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::style_pair,
    (std::string, first)
    (mapnik::rules, second)
);


BOOST_FUSION_ADAPT_ADT(
    mapnik::rule,
    // name
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_name(),mapnik::rule().get_name()), /**/)
    // filter
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(mapnik::to_expression_string(*obj.get_filter()),
                                   mapnik::to_expression_string(*mapnik::rule().get_filter()) ),/**/)
    // zoom levels
    (boost::optional<std::string>, boost::optional<std::string>, cssgen::conv_zoom( \
        cssgen::make_opt<double>(obj.get_min_scale(),mapnik::rule().get_min_scale()),
        cssgen::make_opt<double>(obj.get_max_scale(),mapnik::rule().get_max_scale()) )
     , /**/)
    //// min scale
    //(boost::optional<double>, boost::optional<double>, \
    // cssgen::make_opt<double>(obj.get_min_scale(),mapnik::rule().get_min_scale()) , /**/)    
    //// max scale
    //(boost::optional<double>, boost::optional<double>, \
    // cssgen::make_opt<double>(obj.get_max_scale(),mapnik::rule().get_max_scale()) , /**/)
    // title
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_title(),mapnik::rule().get_title()), /**/)
    // abstract
    (boost::optional<std::string>, boost::optional<std::string>, \
     cssgen::make_opt<std::string>(obj.get_abstract(),mapnik::rule().get_abstract()) , /**/)
    //(bool,   bool,   obj.has_else_filter(), /**/)
    // symbolizers
    (mapnik::rule::symbolizers const&, mapnik::rule::symbolizers const&,  obj.get_symbolizers(), /**/)
);



namespace cssgen {

namespace karma = boost::spirit::karma;

template <typename Iter>
struct style_css_gen : karma::grammar< Iter, style_map() > {
    style_css_gen() : style_css_gen::base_type(styles) {
    
        using karma::omit;
        using karma::string;
        using karma::double_;
        using karma::bool_;
        
        rule  =    -("." << string << " ")
                << -("[" << string << "] ")
                << -(string << " ")
                << "{\n"
                << -("title: " << qstring << ";\n")
                << -("abstract: " << qstring << ";\n")
                //<< -("else_filter: " << bool_ << ";\n")
                << symbolizer % ""
                
                << "}";
                      
        rules  = rule % "\n";
        style  =    "." << string << " {\n"
                 << rules << "\n"
                 << "}";
        styles = style % "\n";
    }

    quoted_string< Iter > qstring;
    symbolizer_gen< Iter > symbolizer;

    karma::rule< Iter, style_map() >  styles;
    karma::rule< Iter, style_pair() > style;
    karma::rule< Iter, mapnik::rules() > rules;
    karma::rule< Iter, mapnik::rule() > rule;
};

}