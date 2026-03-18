/**
 * SPDX-License-Identifier: MIT
 */

#ifndef CYCLIC_STATE_HPP_
#define CYCLIC_STATE_HPP_

#include <iostream>
#include <nlohmann/json.hpp>

namespace cadmium::celldevs::example::cyclic {

    struct cyclicState {
        int phase;
        cyclicState() : phase(0) {}
    };

    inline bool operator != (const cyclicState &x, const cyclicState &y) {
        return x.phase != y.phase;
    }

    inline std::ostream &operator << (std::ostream &os, const cyclicState &x) {
        os << "<" << x.phase << ">";
        return os;
    }

    [[maybe_unused]] inline void from_json(const nlohmann::json& j, cyclicState& s) {
        j.at("phase").get_to(s.phase);
    }

}

#endif