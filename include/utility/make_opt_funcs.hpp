#ifndef MAKE_OPT_FUNCS_HPP
#define MAKE_OPT_FUNCS_HPP

#include <boost/optional.hpp>

namespace cssgen {
    
    template <class T> 
    inline boost::optional<T> make_opt(T val, T dfl_val)
    {
        if (val == dfl_val)
            return boost::optional<T>();

        return boost::optional<T>(val);
    }
    
    /*template <class T> 
    inline boost::optional<T> make_opt_has(T val, bool has)
    {
        if (!has)
            return boost::optional<T>();

        return boost::optional<T>(val);
    }*/
    
    template <class T> 
    inline boost::optional<T> make_opt_empty(T val)
    {
        if (val.empty())
            return boost::optional<T>();

        return boost::optional<T>(val);
    }

}

#endif