#include "gen_building_sym.hpp"

namespace cssgen {

template <typename Iter>
building_sym_gen<Iter>::building_sym_gen() : building_sym_gen::base_type(building_sym) {

    using karma::double_;

    building_sym =     ("building-fill: "         << color   << ";\n")
                   << -("building-fill-opacity: " << double_ << ";\n")
                   << -("building-height: "       << double_ << ";\n");
}

}