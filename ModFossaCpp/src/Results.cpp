/* 
 * File:   Results.cpp
 * Author: gareth
 * 
 * Created on March 29, 2013, 9:22 PM
 */

#include <ModFossa/Results/Results.h>

namespace ModFossa {
Results::Results() {
}

Results::~Results() {
}

Vector3d Results::getStateProbabilities(std::string name) {

    if (name.empty()) {
        throw std::runtime_error("Experiment sweep name cannot be empty");
    }
    
    if (!experimentSweepResultsExist(name)) {
        throw std::runtime_error(
                "ExperimentSweep results " + name + " does not exist");
    }
    return experiment_sweep_probabilities[name];
}

Vector2d Results::getVoltageProtocol(std::string experiment_sweep_name) {
    if (experiment_sweep_name.empty()) {
        throw std::runtime_error("Experiment sweep name cannot be empty");
    }
    
    if (!experimentSweepResultsExist(experiment_sweep_name)) {
        throw std::runtime_error(
                "ExperimentSweep results " + experiment_sweep_name \
                + " does not exist");
    }
    return experiment_sweep_voltage_protocol[experiment_sweep_name];
}


bool Results::experimentSweepResultsExist(std::string name) const {
    ResultsMap3d::const_iterator it;
    it = experiment_sweep_probabilities.find(name);

    if (it != experiment_sweep_probabilities.end()) {
        return true;
    }
    return false;
}

void Results::saveExperimentSweepProbabilities(
        ExperimentSweep::SharedPointer sweep, Vector3d state_probabilities) {
    
    std::string experiment_sweep_name = sweep->getName();
    
    if(experimentSweepResultsExist(experiment_sweep_name)) {
        throw std::runtime_error("Experiment Sweep " + experiment_sweep_name + \
                " already has results saved");
    }
    
    // Save the state probabilities
    experiment_sweep_probabilities[experiment_sweep_name] = state_probabilities;    

    // Transform and save the voltage protocol as a 2d vector
    SerializedProtocolSharedPointer vp = sweep->getSerializedVoltageProtocol();
    
    Vector2d voltage_protocol;
        
    SerializedProtocol::iterator protocol_iterator;
    for(protocol_iterator = vp->begin(); 
            protocol_iterator != vp->end(); 
            ++protocol_iterator) {
        
        voltage_protocol.push_back(Vector());
        int voltage_protocol_iteration_time_step = 0; // ms
       
        for(unsigned int inner_index = 0; 
                inner_index < protocol_iterator->size(); 
                ++inner_index ) {

            double voltage = ((*protocol_iterator)[inner_index]).second;
            
            int change_time_index;
            // We are currently at the last protocol stage
            if(inner_index == protocol_iterator->size() - 1) { 
                change_time_index = inner_index;
            }
            else {
                change_time_index = inner_index + 1;
            }
                
            double voltage_change_time = 
                    ((*protocol_iterator)[change_time_index]).first;

            while(voltage_protocol_iteration_time_step !=
                    voltage_change_time) {

                voltage_protocol.back().push_back(voltage);
                voltage_protocol_iteration_time_step++;
            }
        } 
    }
    experiment_sweep_voltage_protocol[experiment_sweep_name] = 
            voltage_protocol;
}

}
