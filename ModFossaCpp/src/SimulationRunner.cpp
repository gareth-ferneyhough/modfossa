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
    
    Results::SharedPointer SimulationRunner::getResultsClass() const {
        return results;
    }
    
    void SimulationRunner::runAllExperimentSweeps() {
        std::vector<ExperimentSweep::SharedPointer> sweeps = 
                experiment->getAllExperimentSweeps();
        
        std::vector<ExperimentSweep::SharedPointer>::const_iterator it;
        for(it = sweeps.begin(); it != sweeps.end(); ++it) {
            doRunExperimentSweep(*it);
        }
    }

    void SimulationRunner::runExperimentSweep(
            std::string name) {

        // Get the experiment sweep. This will throw if the sweep does not exist.
        ExperimentSweep::SharedPointer experiment_sweep =
                experiment->getExperimentSweep(name);
        
        doRunExperimentSweep(experiment_sweep);
    }
    
    void SimulationRunner::doRunExperimentSweep(
        ExperimentSweep::SharedPointer experiment_sweep) {

        // Make sure that we have already validated the experiment.
        if (!experiment->isValid()) {
            throw std::runtime_error("Experiment must be validated\
                                  before it can be run");
        }

        // Create StateOfTheWorld from ExperimentSweep
        StateOfTheWorld::SharedPointer state_of_the_world(
                new StateOfTheWorld(experiment_sweep->getConcentrationMap()));

        // Create TransitionMatrix
        TransitionMatrix::SharedPointer transition_matrix(
                new TransitionMatrix(*(experiment->getMarkovModel())));

        SerializedProtocolSharedPointer serialized_protocol =
                experiment_sweep->getSerializedVoltageProtocol();


        // Get our results ready
        Vector3d experiment_sweep_results;

        // Run protocol iteration, appending the results to our results each time.
        SerializedProtocol::const_iterator it;
        for (it = serialized_protocol->begin();
                it != serialized_protocol->end(); ++it) {

            experiment_sweep_results.push_back(simulator->runProtocolIteration(
                    *it, state_of_the_world, transition_matrix));
        }

        // Save results. The results class will use the experimentSweep instance
        // and the results we just calculated to generate the various data 
        // required for analysis.
        results->saveExperimentSweepProbabilities(
                experiment_sweep, experiment_sweep_results);
    }

    void SimulationRunner::initialize() {
        experiment = Experiment::SharedPointer(new Experiment());
        simulator = Simulator::SharedPointer(new Simulator());
        results = Results::SharedPointer(new Results());
    }
}
