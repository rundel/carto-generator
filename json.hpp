#include <vector>
#include <map>
#include <utility>

#include <boost/mpl/print.hpp>
#include <boost/fusion/include/std_pair.hpp> 
#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/container/map.hpp> 
#include <boost/variant/recursive_variant.hpp>

namespace json {

    struct keyval;
    struct object;
    struct array;

    typedef boost::variant< 
        boost::recursive_wrapper<object>, 
        boost::recursive_wrapper<array>, 
        std::string, double, bool > value;

    struct keyval : std::pair< std::string, value > {};
    struct object : std::map< std::string, value> {};
    struct array : std::vector<value>{};
    
    typedef std::pair< std::string, value > TDkeyval;
}

BOOST_FUSION_ADAPT_STRUCT(
    json::keyval,
    (std::string, first)
    (json::value, second)
);