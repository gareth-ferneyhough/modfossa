/* 
 * File:   SimulationRunner.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 9:23 PM
 */

#include <ModFossa/Experiment/SimulationRunner.h>

namespace ModFossa {

    SimulationRunner::SimulationRunner() {
        initialize();
    }

    SimulationRunner::~SimulationRunner() {
    }

    Experiment::SharedPointer SimulationRunner::getExperiment() const {
        return experiment;
    }

    void SimulationRunner::runExperimentSweep(std::string experiment_sweep_name) {

        // Make sure that we have already validated the experiment.
        if (!experiment->isValid()) {
            throw std::runtime_error("Experiment must be validated\
                                  before it can be run");
        }

        // Get the experiment sweep. This will throw if the sweep does not exist.
        ExperimentSweep::SharedPointer experiment_sweep =
                experiment->getExperimentSweep(experiment_sweep_name);


        // Create StateOfTheWorld from ExperimentSweep
        StateOfTheWorld::SharedPointer state_of_the_world(
                new StateOfTheWorld(experiment_sweep->getConcentrationMap()));

        // Create TransitionMatrix
        TransitionMatrix::SharedPointer transition_matrix(
                new TransitionMatrix(*(experiment->getMarkovModel())));

        SerializedProtocolSharedPointer serialized_protocol =
                experiment_sweep->getSerializedVoltageProtocol();


        // Get our results ready
        ExperimentSweepResults results;

        // Run protocol iteration, appending the results to our results each time.
        SerializedProtocol::const_iterator it;
        for (it = serialized_protocol->begin();
                it != serialized_protocol->end(); ++it) {

            results.push_back(simulator->runProtocolIteration(
                    *it, state_of_the_world, transition_matrix));
        }

        // Save results to map
        results_map[experiment_sweep_name] = results;
    }

    void SimulationRunner::initialize() {
        experiment = Experiment::SharedPointer(new Experiment());
        simulator = Simulator::SharedPointer(new Simulator());
    }
}
