/* 
 * File:   Experiment.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:06 PM
 */

#ifndef EXPERIMENT_H
#define	EXPERIMENT_H

#include <map>
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
    
    Experiment();
    ~Experiment();
    
    void addVoltageProtocol(VoltageProtocol::SharedPointer voltage_protocol);
    void addExperimentSweep(ExperimentSweep::SharedPointer experiment_sweep);
    void runExperimentSweep();
        
private:
    MarkovModel::SharedPtr markov_model;
    VoltageProtocolMap voltage_protocols;
    ExperimentSweepMap experiment_sweeps;
    
    void createExperimentSweepInternalData();


};
}

#endif	/* EXPERIMENT_H */

