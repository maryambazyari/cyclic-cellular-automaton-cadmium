#ifndef CYCLIC_COUPLED_HPP_
#define CYCLIC_COUPLED_HPP_

#include <cadmium/celldevs/coupled/grid_coupled.hpp>
#include "cyclic_grid_cell.hpp"

template <typename T>
class cyclic_coupled : public cadmium::celldevs::grid_coupled<T, cadmium::celldevs::example::cyclic::cyclicState, cadmium::celldevs::example::cyclic::cyclic_vicinity> {
public:
    using cyclicState = cadmium::celldevs::example::cyclic::cyclicState;
    using cyclic_vicinity = cadmium::celldevs::example::cyclic::cyclic_vicinity;

    explicit cyclic_coupled(std::string const& id)
        : cadmium::celldevs::grid_coupled<T, cyclicState, cyclic_vicinity>(id) {}

    void add_grid_cell_json(std::string const& cell_type,
                            cell_map<cyclicState, cyclic_vicinity>& map,
                            std::string const& delay_id,
                            cadmium::json const& config) override {
        int conf = 0;
        if (!config.is_null()) {
            try { conf = config.get<int>(); } catch (...) { conf = 0; }
        }

        if (cell_type == "cyclic" || cell_type == "default") {
            this->template add_cell<cadmium::celldevs::example::cyclic::GridCyclicCell>(map, delay_id, conf);
        } else {
            throw std::bad_typeid();
        }
    }
};

#endif