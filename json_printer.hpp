namespace json {
    ///////////////////////////////////////////////////////////////////////////
    //  Print out the json tree
    ///////////////////////////////////////////////////////////////////////////
    int const tabsize = 4;

    void tab(int indent) {
        for (int i = 0; i < indent; ++i) std::cout << ' ';
    }

    struct json_printer {
        
        json_printer(int indent = 0) : indent(indent) {}
        void operator()(value const& val) const;

        int indent;
    };

    struct json_object_printer {
        
        json_object_printer(int indent = 0) : indent(indent) {}
        void operator()(object const& obj) const;

        int indent;
    };

    struct json_array_printer {
        
        json_array_printer(int indent = 0) : indent(indent) {}
        void operator()(array const& arr) const;

        int indent;
    };

    struct json_value_printer : boost::static_visitor<> {
        
        json_value_printer(int indent = 0) : indent(indent) {
        }

        void operator()(object const& obj) const {
            json_object_printer printer(indent);
            printer(obj);
        }

        void operator()(array const& arr) const {
            json_array_printer printer(indent);
            printer(arr);
        }

        void operator()(std::string const& text) const {
            std::cout << '"' << text << '"';
        }

        void operator()(double const& d) const {
            std::cout << d;
        }
        
        void operator()(bool const& b) const {
            if (b) {
                std::cout << "true";
            } else {
                std::cout << "false";
            }
        }

        int indent;
    };


    void json_printer::operator()(value const& val) const {
        boost::apply_visitor(json_value_printer(indent), val);
        std::cout << std::endl;
    }

    void json_object_printer::operator()(object const& obj) const {
        
        std::cout << '{' << std::endl;

        int curindent = indent + tabsize;

        /*BOOST_FOREACH(TDkeyval const& node, obj) {
            tab(curindent);
            std::cout << '"' << node.first << "\" : ";
            boost::apply_visitor(json_value_printer(curindent), node.second);
            std::cout << "," << std::endl;
        }*/
        
        
        object::const_iterator last = --obj.end();
        
        for(object::const_iterator iter = obj.begin(); iter != obj.end(); ++iter) {
            tab(curindent);
            std::cout << '"' << iter->first << "\" : ";
            boost::apply_visitor(json_value_printer(curindent), iter->second);
            
            if (iter != last)
                std::cout << ",";
            
            std::cout << std::endl;
        }
        
        
        
        tab(indent);
        std::cout << '}';
    }
    
    void json_array_printer::operator()(array const& arr) const {
        
        std::cout << "[ " << std::endl;

        /*BOOST_FOREACH(value const& val, arr) {
            boost::apply_visitor(json_value_printer(indent), val);
            std::cout << "," << std::endl;
        }*/
        
        int curindent = indent + tabsize;
                
        array::const_iterator last = --arr.end();
        
        for(array::const_iterator iter = arr.begin(); iter != arr.end(); ++iter) {
            tab(curindent);
            boost::apply_visitor(json_value_printer(curindent), *iter);
            
            if (iter != last)
                std::cout << ",";
            
            std::cout << std::endl;
        }


        tab(indent);
        std::cout << ']';
    }
    
}