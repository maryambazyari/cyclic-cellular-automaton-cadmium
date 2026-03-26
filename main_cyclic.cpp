/**
 * SPDX-License-Identifier: MIT
 */

#include <string>
#include <fstream>
#include <memory>

#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

#include "include/cyclic_coupled.hpp"

using namespace std;
using namespace cadmium;
using namespace cadmium::celldevs::example::cyclic;

using TIME = double;

static ofstream out_messages("cyclic_grid_log.csv");

struct oss_sink_messages {
    static ostream& sink() {
        return out_messages;
    }
};

using log_messages = logger::logger<
    logger::logger_messages,
    dynamic::logger::formatter<TIME>,
    oss_sink_messages
>;

using global_time_mes = logger::logger<
    logger::logger_global_time,
    dynamic::logger::formatter<TIME>,
    oss_sink_messages
>;

using logger_top = logger::multilogger<log_messages, global_time_mes>;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Program used with wrong parameters. The program must be invoked as follows:\n";
        cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 50)]" << endl;
        return -1;
    }

    string configFilePath = argv[1];
    TIME simTime = (argc > 2) ? stod(argv[2]) : 50.0;

    cyclic_coupled<TIME> test = cyclic_coupled<TIME>("cyclic");
    test.add_lattice_json(configFilePath);
    test.couple_cells();

    shared_ptr<dynamic::modeling::coupled<TIME>> t = make_shared<cyclic_coupled<TIME>>(test);

    dynamic::engine::runner<TIME, logger_top> r(t, {0});
    r.turn_progress_on();
    r.run_until(simTime);

    return 0;
}