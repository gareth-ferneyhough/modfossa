/* 
 * File:   Experiment.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 12:06 PM
 */

#include <ModFossa/Experiment/Experiment.h>

namespace ModFossa {
using std::string;

Experiment::Experiment() {
    initialize();
}

Experiment::~Experiment() {
}

MarkovModel::SharedPtr Experiment::getMarkovModel() const {
    return markov_model;
}

void Experiment::initialize() {
    markov_model = MarkovModel::SharedPtr(new MarkovModel());
    is_valid = false;
}

void Experiment::serializeExperimentSweep(std::string name) {

}

ExperimentSweep::SharedPointer Experiment::getExperimentSweep(std::string name){
    if(!experimentSweepExists(name)) {
        throw std::runtime_error(
            "ExperimentSweep " + name + " does not exist");
    }
}

void Experiment::addVoltageProtocol(
        VoltageProtocol::SharedPointer voltage_protocol) {
    
    string name = voltage_protocol->getName();
    if (voltageProtocolExists(name)) {
        throw std::runtime_error(
            "VoltageProtocol with name " + name + " already exists");
    }
    
    if (voltage_protocol->isEmpty()) {
        throw std::runtime_error(
            "VoltageProtocol " + name + " has no stages defined");
    }
    
    voltage_protocols[name] = voltage_protocol;
    is_valid = false;
    
}
void Experiment::addExperimentSweep(
        ExperimentSweep::SharedPointer experiment_sweep) {
    
    string name = experiment_sweep->getName();
    if (experimentSweepExists(name)) {
        throw std::runtime_error(
                "ExperimentSweep with name " + name + " already exists");
    }

    experiment_sweeps[name] = experiment_sweep;
    is_valid = false;
    
}

bool Experiment::isValid() const {
    return is_valid;
}



bool Experiment::voltageProtocolExists(string name) const {
    VoltageProtocolMap::const_iterator it;
    it = voltage_protocols.find(name);

    if (it != voltage_protocols.end()) {
        return true;
    }
    return false;
}

bool Experiment::experimentSweepExists(string name) const {
    ExperimentSweepMap::const_iterator it;
    it = experiment_sweeps.find(name);

    if (it != experiment_sweeps.end()) {
        return true;
    }
    return false;
}

Validation::ValidationResults Experiment::validateExperimentSweep(
        ExperimentSweep::SharedPointer experiment_sweep) {
    
    using namespace Validation;

    // for each experiment sweep:
        // check that its voltage protocol exists
        // set the reference to its serialized data
        // generate a state of the world
        // validate the markov model with the state of the world
       
        //ValidationResults mm_validation_results = 
          //      markov_model->validate(state_of_the_world);
        
        
}

Validation::ValidationResults Experiment::validate() {
    using namespace Validation;

    ValidationResults::ErrorVector errors;
    ErrorLevel error_level = NO_WARNINGS;

    // check for at least one voltage protocol
    if(voltage_protocols.empty()) {
        errors.push_back(std::make_pair(        
                NO_VOLTAGE_PROTOCOLS,
                "no VoltageProtocol defined"));
        
        error_level = ERRORS;
    }
    
    // check for at least one experiment sweep
    if(experiment_sweeps.empty()) {
        errors.push_back(std::make_pair(        
                NO_EXPERIMENT_SWEEPS,
                "no ExperimentSweeps defined"));
        
        error_level = ERRORS;
    }
    
    // for each voltage protocol, serialize its data
//    VoltageProtocolMap::const_iterator it;
//    for(it = voltage_protocols.begin(); it != voltage_protocols.end(); ++it) {
//        it->second->
//    }
//    
    
    // for each experiment sweep:
        // check that its voltage protocol exists
        // set the reference to its serialized data
        // generate a state of the world
        // validate the markov model with the state of the world

    
    
    // check connections that rate_constants and states exist
//    for (unsigned int i = 0; i < connections.size(); ++i) {
//
//        string from_state = connections[i]->from_state;
//        string to_state = connections[i]->to_state;
//        string rate_name = connections[i]->rate_name;
//
//        if (!stateExists(from_state)) {
//            errors.push_back(std::make_pair(
//                    STATE_NOT_DEFINED,
//                    "State not defined: " + from_state));
//
//            error_level = ERRORS;
//        }
//
//        if (!stateExists(to_state)) {
//            errors.push_back(std::make_pair(
//                    STATE_NOT_DEFINED,
//                    "State not defined: " + to_state));
//
//            error_level = ERRORS;
//        }
//
//        if (!rateConstantExists(rate_name)) {
//            errors.push_back(std::make_pair(
//                    RATE_CONSTANT_NOT_DEFINED,
//                    "Rate constant not defined: " + rate_name));
//
//            error_level = ERRORS;
//        }
//    }
//
//    if (state_of_the_world == NULL) {
//        errors.push_back(std::make_pair(
//                STATE_OF_THE_WORLD_IS_NULL,
//                "state_of_the_world cannot be NULL"));
//
//        error_level = ERRORS;
//    }
//
//    // TODO: Add warnings for unused states and rates.
//
//    if (state_of_the_world != NULL) {
//        // Check that each LigandGated rate constant has its ligand 
//        // defined in state_of_the_world
//        RateMap::const_iterator it;
//        for (it = map_of_rates.begin(); it != map_of_rates.end(); ++it) {
//            try {
//                it->second->getRate(state_of_the_world);
//            } catch (std::runtime_error& e) {
//                errors.push_back(std::make_pair(
//                        LIGAND_NOT_DEFINED,
//                        // This is a bad and ugly message!
//                        "Ligand not defined: " + string(e.what())));
//
//                error_level = ERRORS;
//            }
//        }
//    }
//
//    /* If everything is valid, set the validation flag so that no changes
//     * can be made without re-validating. Also, we need to assign indices 
//     * to all the states. Both of the transition matrices will be size NxN, 
//     * where N is the number of states. State with index 0 will occupy the 
//     * 0th row and column of the matrices.   
//     * 
//     * Also, assign the initial_state flag to the state which was 
//     * designated so.
//     */
//    if (error_level != ERRORS) {
//        StateMap::iterator it;
//        int index = 0;
//        for (it = map_of_states.begin(); it != map_of_states.end(); ++it) {
//            it->second->index = index;
//            ++index;
//
//            if (it->first == initial_state) {
//                it->second->is_initial_state = true;
//            }
//        }
//        is_valid = true;
//    }

    ValidationResults results(error_level, errors);
    return results;
}


}
