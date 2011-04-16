namespace cssgen {

    struct rule_data {
        
        boost::optional<std::string> name_;
        boost::optional<std::string> title_;
        boost::optional<std::string> abstract_;
        boost::optional<double> min_scale_;
        boost::optional<double> max_scale_;
        //mapnik::symbolizers syms_;
        //mapnik::expression_ptr filter_;
        boost::optional<bool> else_filter_;
        
        rule_data(mapnik::rule const& rhs) {
            mapnik::rule defaults();
            
            name_ = rhs.get_name();
            title_ = rhs.get_title();
            abstract_ = rhs.get_abstract();
            
            if(rhs.get_min_scale() != mapnik::rule().get_min_scale())
                min_scale_ = rhs.get_min_scale();
                
            if(rhs.get_max_scale() != mapnik::rule().get_max_scale())
                max_scale_ = rhs.get_max_scale();
            
            else_filter_ = rhs.has_else_filter();
            
            //syms_ = rhs.get_symbolizers();
            //filter_ = rhs.get_filter();
        }
    };
}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::rule_data,
    (boost::optional<std::string>, name_)
    (boost::optional<std::string>, title_)
    (boost::optional<std::string>, abstract_)
    (boost::optional<double>, min_scale_)
    (boost::optional<double>, max_scale_)
    (boost::optional<bool>, else_filter_)
    //(mapnik::symbolizers, syms_)
    //(mapnik::expression_ptr, filter_)
);