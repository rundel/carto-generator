#ifndef GEN_DASH_PAIR
#define GEN_DASH_PAIR

#include <boost/fusion/include/adapt_struct.hpp> 

namespace cssgen {

typedef std::pair<double,double> dash_pair;

}

BOOST_FUSION_ADAPT_STRUCT(
    cssgen::dash_pair,
    (double, first)
    (double, second)
);

#endif