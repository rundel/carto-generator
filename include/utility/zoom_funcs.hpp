#ifndef ZOOM_FUNCS_HPP
#define ZOOM_FUNCS_HPP

namespace cssgen {

inline int find_zoom(double denom, bool max)
{
    const int max_zoom = 22;
    const double zoom_ranges[] = { 1000000000, 500000000, 200000000, 100000000,
                                     50000000,  25000000,  12500000,   6500000,
                                      3000000,   1500000,    750000,    400000,
                                       200000,    100000,     50000,     25000,
                                        12500,      5000,      2500,      1500,
                                          750,       500,       250,       100};

    for(int i = 0; i <= max_zoom; i++) {

        if (zoom_ranges[i] == denom) 
            return i;

        if (zoom_ranges[i] < denom)
            return i-(int)max;
    }

    return (max) ? 0 : max_zoom;
}



inline boost::optional<std::string> conv_zoom(boost::optional<double> scale_min, boost::optional<double> scale_max)
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

#endif