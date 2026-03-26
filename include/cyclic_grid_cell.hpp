/**
 * SPDX-License-Identifier: MIT
 */

#ifndef CYCLIC_GRID_CELL_HPP_
#define CYCLIC_GRID_CELL_HPP_

#include <cmath>
#include <ostream>
#include <nlohmann/json.hpp>
#include <cadmium/celldevs/cell/grid_cell.hpp>

#include "cyclic_state.hpp"

using cadmium::json;
using namespace cadmium::celldevs;

namespace cadmium::celldevs::example::cyclic {

struct cyclic_vicinity {
    int value;
    cyclic_vicinity() : value(1) {}
};

inline void from_json(const json& j, cyclic_vicinity& v) {
    if (j.is_number_integer()) {
        j.get_to(v.value);
    } else {
        v.value = 1;
    }
}

template <typename T>
class GridCyclicCell : public grid_cell<T, cyclicState, cyclic_vicinity> {
public:
    using grid_cell<T, cyclicState, cyclic_vicinity>::state;
    using grid_cell<T, cyclicState, cyclic_vicinity>::neighbors;

    GridCyclicCell() : grid_cell<T, cyclicState, cyclic_vicinity>() {}

    GridCyclicCell(
        cell_position const& cell_id,
        cell_unordered<cyclic_vicinity> const& neighborhood,
        cyclicState initial_state,
        cell_map<cyclicState, cyclic_vicinity> const& map_in,
        std::string const& delay_id,
        int
    ) : grid_cell<T, cyclicState, cyclic_vicinity>(cell_id, neighborhood, initial_state, map_in, delay_id) {}

    cyclicState local_computation() const override {
        cyclicState result = state.current_state;

        bool has0 = false;
        bool has1 = false;
        bool has2 = false;

        for (const auto& neighbor : neighbors) {
            cyclicState n = state.neighbors_state.at(neighbor);
            if (n.phase == 0) has0 = true;
            else if (n.phase == 1) has1 = true;
            else if (n.phase == 2) has2 = true;
        }

        if (result.phase == 0 && has1) {
            result.phase = 1;
        } else if (result.phase == 1 && has2) {
            result.phase = 2;
        } else if (result.phase == 2 && has0) {
            result.phase = 0;
        }

        return result;
    }

    T output_delay(cyclicState const&) const override {
        return T(1);
    }
};

}

#endif