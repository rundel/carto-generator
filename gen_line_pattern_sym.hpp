
BOOST_FUSION_ADAPT_ADT(
    mapnik::line_pattern_symbolizer,
    // line-pattern-file
    (boost::optional<std::string>,
     boost::optional<std::string>,
     cssgen::make_opt_empty<std::string>(mapnik::path_processor_type::to_string(*obj.get_filename()) ),
     /**/)
);

namespace cssgen {

    namespace karma = boost::spirit::karma;
    
    template <typename Iter>
    struct line_pattern_sym_gen : karma::grammar< Iter, mapnik::line_pattern_symbolizer() > {
        line_pattern_sym_gen() : line_pattern_sym_gen::base_type(line_pattern_sym) {
        
            line_pattern_sym = -("line-pattern-file: "      << qstring   << ";\n");
            
        }
        
        quoted_string< Iter > qstring;
        karma::rule< Iter, mapnik::line_pattern_symbolizer() > line_pattern_sym;
    };
}

