/* 
 * File:   Experiment.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:06 PM
 */

#ifndef EXPERIMENT_H
#define	EXPERIMENT_H

#include <map>
#include <ModFossa/Common/ContainerTypes.h>
#include <ModFossa/ModelDefinition/MarkovModel.h>
#include <ModFossa/Experiment/VoltageProtocol.h>
#include <ModFossa/Experiment/ExperimentSweep.h>

namespace ModFossa {
class Experiment {
public:
    typedef std::map<const std::string, VoltageProtocol::SharedPointer > 
        VoltageProtocolMap;
    typedef std::map<const std::string, ExperimentSweep::SharedPointer > 
        ExperimentSweepMap;
    typedef shared_ptr<Experiment>::type SharedPointer;
    
    Experiment();
    ~Experiment();
    
    /**
     * Add VoltageProtocol to the map of VoltageProtocols. A runtime error
     * will be thrown if the VoltageProtocol is empty, ie has no stages defined,
     * or if a VoltageProtocol with the same name already exists in the map.
     * 
     * @param voltage_protocol The VoltageProtocol to add to the map of 
     * VoltageProtocols.
     */
    void addVoltageProtocol(VoltageProtocol::SharedPointer voltage_protocol);    
    
    /**
     * Add ExperimentSweep to the map of ExperimentSweeps. A runtime error
     * will be thrown if an ExperimentSweep with the same name already exists in
     * the map.
     * 
     * @param experiment_sweep The ExperimentSweep to add to the map of
     * ExperimentSweeps.
     */
    void addExperimentSweep(ExperimentSweep::SharedPointer experiment_sweep);    
    
    
    MarkovModel::SharedPointer getMarkovModel() const;
    
    /**
     * Validate the Experiment. This will perform several checks. They include,
     * checking that at least one VoltageProtocol and ExperimentSweep exist,
     * and that each ExperimentSweep is valid and generates a StateOfTheWorld
     * instance that the MarkovModel is valid against.
     * 
     * The validate method will generate internal data structures for each
     * VoltageProtocol. If any changes are made to the MarkovModel, or any
     * VoltageProtocol or ExperimentSweep, validate will have to be called 
     * again.
     * 
     * Validation will continue if validation errors are encountered. This way,
     * the user will be notified of every error in the experiment and Markov
     * Model.
     * 
     * @return ValidationResults structure containing the overall validation
     * result, and a vector of error types with textual descriptions, if any.
     * 
     */
    Validation::ValidationResults validate();
    
    std::vector<ExperimentSweep::SharedPointer> getAllExperimentSweeps();
    ExperimentSweep::SharedPointer getExperimentSweep(std::string name);
    VoltageProtocol::SharedPointer getVoltageProtocol(std::string name);
    
    ////
    //shared_ptr<Validation::ValidationResults>::type validate2();
    std::vector<std::string> validate3();
    ///
    
    
    bool isValid() const;
        
private:
    friend class SimulationRunner;
        
    MarkovModel::SharedPointer markov_model;
    VoltageProtocolMap voltage_protocols;
    ExperimentSweepMap experiment_sweeps;
    
    bool is_valid;
    
    bool voltageProtocolExists(std::string name) const;
    bool experimentSweepExists(std::string name) const;    
    void initialize();
    
    void serializeExperimentSweep(std::string name);

    
    /**
     * Validate a single ExperimentSweep. The corresponding VoltageProtocol
     * will be located and serialized. The ExperimentSweep will be given a 
     * pointer to the serialized data. Then a StateOfTheWorld will be 
     * constructed using the ExperimentSweep, and our MarkovModel will be
     * validated using the StateOfTheWorld. All errors will be saved to the 
     * ValidationResults and returned.
     * 
     * @param experiment_sweep
     * @return 
     * 
     */
    Validation::ValidationResults validateExperimentSweep(
        ExperimentSweep::SharedPointer experiment_sweep);
    
};
}

#endif	/* EXPERIMENT_H */

