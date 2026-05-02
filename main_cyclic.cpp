#include <cadmium/celldevs/grid/coupled.hpp>
#include <cadmium/core/logger/csv.hpp>
#include <cadmium/core/simulation/root_coordinator.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include "include/cyclic_grid_cell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium::celldevs::example::cyclic;

std::shared_ptr<GridCell<cyclicState, double>> addGridCell(
    const coordinates& cellId,
    const std::shared_ptr<const GridCellConfig<cyclicState, double>>& cellConfig
) {
    auto cellModel = cellConfig->cellModel;
    if (cellModel == "default" || cellModel == "cyclic") {
        return std::make_shared<GridCyclicCell>(cellId, cellConfig);
    } else {
        throw std::bad_typeid();
    }
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0]
                  << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME]" << std::endl;
        return -1;
    }

    std::string configFilePath = argv[1];
    double simTime = (argc > 2) ? std::stod(argv[2]) : 50.0;

    auto paramsProcessed = std::chrono::high_resolution_clock::now();

    auto model = std::make_shared<GridCellDEVSCoupled<cyclicState, double>>(
        "cyclic", addGridCell, configFilePath
    );
    model->buildModel();

    auto modelGenerated = std::chrono::high_resolution_clock::now();
    std::cout << "Model creation time: "
              << std::chrono::duration_cast<std::chrono::duration<double>>(modelGenerated - paramsProcessed).count()
              << " seconds" << std::endl;

    auto rootCoordinator = cadmium::RootCoordinator(model);
    auto logger = std::make_shared<cadmium::CSVLogger>("cyclic_grid_log.csv", ";");
    rootCoordinator.setLogger(logger);
    rootCoordinator.start();

    auto engineStarted = std::chrono::high_resolution_clock::now();
    std::cout << "Engine creation time: "
              << std::chrono::duration_cast<std::chrono::duration<double>>(engineStarted - modelGenerated).count()
              << " seconds" << std::endl;

    rootCoordinator.simulate(simTime);

    auto simulationDone = std::chrono::high_resolution_clock::now();
    std::cout << "Simulation time: "
              << std::chrono::duration_cast<std::chrono::duration<double>>(simulationDone - engineStarted).count()
              << " seconds" << std::endl;

    rootCoordinator.stop();
    return 0;
}