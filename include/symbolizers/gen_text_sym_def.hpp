#include "symbolizers/gen_text_sym.hpp"

namespace cssgen {

template <typename Iter>
text_sym_gen<Iter>::text_sym_gen() : text_sym_gen::base_type(text_sym) {
        
        using karma::double_;
        using karma::bool_;
        using karma::uint_;
        using karma::string;
        
        text_sym =     ("text-name: "                      << qstring    << ";\n")
                   << -("text-face-name: "                 << qstring    << ";\n")
                   << -("text-face-name: @"                << string     << ";\n")
                   << -("text-size: "                      << uint_      << ";\n")
                   << -("text-ratio: "                     << uint_      << ";\n")
                   << -("text-wrap-width: "                << uint_      << ";\n")
                   << -("text-spacing: "                   << uint_      << ";\n")
                   << -("text-character-spacing: "         << uint_      << ";\n")
                   << -("text-line-spacing: "              << uint_      << ";\n")
                   << -("text-label-position-tolerance: "  << uint_      << ";\n")
                   << -("text-max-char-angle-delta: "      << double_    << ";\n")
                   << -("text-fill: "                      << color      << ";\n")
                   << -("text-halo-fill: "                 << color      << ";\n")
                   << -("text-halo-radius: "               << double_    << ";\n")
                   << -("text-dx: "                        << double_    << ";\n")
                   << -("text-dy: "                        << double_    << ";\n")
                   << -("text-vertical-alignment: "        << string     << ";\n")
                   << -("text-avoid-edges: "               << bool_      << ";\n")
                   << -("text-min-distance: "              << double_    << ";\n")
                   << -("text-min-padding: "               << double_    << ";\n")
                   << -("text-allow-overlap: "             << bool_      << ";\n")
                   << -("text-placement: "                 << string     << ";\n")
                   << -("text-transform: "                 << string     << ";\n");
    }
}