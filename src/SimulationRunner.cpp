/* 
 * File:   SimulationRunner.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 9:23 PM
 */

#include <boost/chrono/chrono.hpp>
#include <ModFossa/Experiment/SimulationRunner.h>

namespace ModFossa {

    SimulationRunner::SimulationRunner() : 
        simulation_has_been_run(false) {
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
    
    void SimulationRunner::runAllExperimentSweeps(
        bool start_at_steady_state) {
        // Start timer.
        boost::chrono::system_clock::time_point start = 
            boost::chrono::system_clock::now();

        if(simulation_has_been_run) {
            throw std::runtime_error("experiment can only be run once");
        }
        simulation_has_been_run = true;
        
        // First, initialize the results class with a pointer to the experiment.
        // Initialization will set the relevant experiment information such as
        // channel conductance, state names and gating variables, reversal
        // potential, etc.
        results->initialize(experiment);
        
        
        std::vector<ExperimentSweep::SharedPointer> sweeps = 
                experiment->getAllExperimentSweeps();
        
        std::vector<ExperimentSweep::SharedPointer>::const_iterator it;
        for(it = sweeps.begin(); it != sweeps.end(); ++it) {
            doRunExperimentSweep(*it, start_at_steady_state);
        }

        // Stop timer
        boost::chrono::duration<double> sec = 
            boost::chrono::system_clock::now() - start;

        std::cout << "time elapsed in runAllExperimentSweeps(): " 
            << sec.count() << " seconds" << std::endl;
    }
    
    void SimulationRunner::doRunExperimentSweep(
        ExperimentSweep::SharedPointer experiment_sweep,
        bool start_at_steady_state) {

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
        Vector3dSharedPtr experiment_sweep_state_probabilities(new Vector3d());

        // Run protocol iteration, appending the results to our results each time.
        SerializedProtocol::const_iterator it;
        for (it = serialized_protocol->begin();
                it != serialized_protocol->end(); ++it) {

            experiment_sweep_state_probabilities->push_back(
                simulator->runProtocolIteration(
                        *it, state_of_the_world, 
                        transition_matrix, 
                        start_at_steady_state));
        }

        // Save results. The results class will use the experimentSweep instance
        // and the results we just calculated to generate the various data 
        // required for analysis.
        results->createExperimentSweepResults(
                experiment_sweep, experiment_sweep_state_probabilities);
    }

    void SimulationRunner::initialize() {
        experiment = Experiment::SharedPointer(new Experiment());
        simulator = Simulator::SharedPointer(new Simulator());
        results = Results::SharedPointer(new Results());
    }
}
