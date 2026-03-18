/**
 * SPDX-License-Identifier: MIT
 */

#ifndef CYCLIC_GRID_CELL_HPP_
#define CYCLIC_GRID_CELL_HPP_

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/celldevs/grid/cell.hpp>
#include <cadmium/celldevs/grid/config.hpp>
#include "cyclic_state.hpp"

namespace cadmium::celldevs::example::cyclic {

    class GridCyclicCell : public GridCell<cyclicState, double> {
    public:
        GridCyclicCell(
            const std::vector<int>& id,
            const std::shared_ptr<const GridCellConfig<cyclicState, double>>& config
        ) : GridCell<cyclicState, double>(id, config) {}

        [[nodiscard]] cyclicState localComputation(
            cyclicState state,
            const std::unordered_map<std::vector<int>, NeighborData<cyclicState, double>>& neighborhood
        ) const override {

            bool has0 = false;
            bool has1 = false;
            bool has2 = false;

            for (const auto& [neighborId, neighborData] : neighborhood) {
                if (neighborData.state == nullptr) continue;

                int p = neighborData.state->phase;
                if (p == 0) has0 = true;
                else if (p == 1) has1 = true;
                else if (p == 2) has2 = true;
            }

            if (state.phase == 0 && has1) {
                state.phase = 1;
            } else if (state.phase == 1 && has2) {
                state.phase = 2;
            } else if (state.phase == 2 && has0) {
                state.phase = 0;
            }

            return state;
        }

        [[nodiscard]] double outputDelay(const cyclicState& state) const override {
            return 1.0;
        }
    };

}

#endif