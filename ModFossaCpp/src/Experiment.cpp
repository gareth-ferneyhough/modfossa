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

MarkovModel::SharedPointer Experiment::getMarkovModel() const {
    return markov_model;
}

void Experiment::initialize() {
    markov_model = MarkovModel::SharedPointer(new MarkovModel());
    is_valid = false;
}

void Experiment::serializeExperimentSweep(std::string name) {

}

ExperimentSweep::SharedPointer Experiment::getExperimentSweep(std::string name){
    if(!experimentSweepExists(name)) {
        throw std::runtime_error(
            "ExperimentSweep " + name + " does not exist");
    }
    return experiment_sweeps[name];
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
    
    ValidationResults::ErrorVector errors;
    ErrorLevel error_level = NO_WARNINGS;

    // Check that the experiment_sweep's voltage protocol exists
    string vp_name = experiment_sweep->getVoltageProtocolName();
    string exp_name = experiment_sweep->getName();
    if(!voltageProtocolExists(vp_name)) {
        errors.push_back(std::make_pair(        
            VOLTAGE_PROTOCOL_NOT_DEFINED,
            "VoltageProtocol " + vp_name + " referenced by "\
                + exp_name + " not defined"));
        
        error_level = ERRORS;
    }
    
    // Save the errors from above.
    ValidationResults return_val(error_level, errors);
    
    if(error_level != ERRORS) {
        // The voltage_protocol exists, so generate its serialized data and set
        // the reference inside our experiment_sweep
        VoltageProtocol::SharedPointer voltage_protocol = 
                voltage_protocols[vp_name];

        experiment_sweep->setSerializedProtocol(
            voltage_protocol->serializeVoltageProtocol());


        // experiment_sweep is now ready to be used by the solver.
        // Lets generate a StateOfTheWorld instance from it and validate  
        // our MarkovModel with the StateOfTheWorld.

        const StateOfTheWorld::SharedPointer temp_state_of_the_world(
        new StateOfTheWorld(experiment_sweep->getConcentrationMap()));
        
        return_val.AppendAdditionalResults(
                markov_model->validate(temp_state_of_the_world));
    }
    
    // If we had errors above (could not find the voltage protocol), then try
    // to validate the MarkovModel with an empty state of the world. This will 
    // produce errors of course, but will return validation information about 
    // the MarkovModel that the user may find helpful.
    else {
        return_val.AppendAdditionalResults(
                markov_model->validate(NULL));
    }
    
    return return_val;
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
    
    // Create validation results structure. We will append additional 
    // information to it further down.
    ValidationResults validation_results(error_level, errors);
    
    // for each experiment sweep:
        // check that its voltage protocol exists
        // set the reference to its serialized data
        // generate a state of the world
        // validate the markov model with the state of the world

    ExperimentSweepMap::iterator it;
    for(it = experiment_sweeps.begin(); it != experiment_sweeps.end(); ++it) {
        validation_results.AppendAdditionalResults(
                validateExperimentSweep(it->second));
    }
    
    // Just so we don't leave the MarkovModel out of the validation, lets
    // validate it even if we don't have any ExperimentSweeps.
    if(experiment_sweeps.empty()) {
        validation_results.AppendAdditionalResults(
                markov_model->validate(NULL));
    }
    
    

    /* If everything is valid, set the validation flag so that no changes
     * can be made without re-validating. 
     */
    if (error_level != ERRORS) {
        is_valid = true;
    }
    return validation_results;
}
}
