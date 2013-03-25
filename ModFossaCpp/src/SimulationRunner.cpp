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

void SimulationRunner::runExperimentSweep(std::string experiment_sweep_name) {
    
    // Serialize experiment sweep by getting the voltage protocol data that
    // it references. This will throw a runtime error if the sweep does not
    // exist, or the voltage protocol it references does not exist, or is empty.
    //experiment->serializeExperimentSweep(experiment_sweep_name);
    
    // Get the experiment sweep we just serialized
    ExperimentSweep::SharedPointer experiment_sweep = 
            experiment->getExperimentSweep(experiment_sweep_name);
    

    // Create state of the world from experiment_sweep concentration map
    //StateOfTheWorld::SharedPointer state_of_the_world(
      //  new StateOfTheWorld(experiment_sweep->getConcentrationMap()));
    
    // Ensure markovModel is valid with state_of_the_world
    //ValidationResults MarkovModel::SharedPtr->validate(state_of_the_world);
    
    
    // create transition_matrix
    
    // for each protocol_iteration in experiment_sweep.get_serialized_voltage_protocol
        // runProtocolIteration()
    
}

void SimulationRunner::initialize() {
    experiment = Experiment::SharedPointer(new Experiment());
    simulator = Simulator::SharedPointer(new Simulator());
}


}
