/* 
 * File:   Results.h
 * Author: gareth
 *
 * Created on March 29, 2013, 9:22 PM
 */

#ifndef RESULTS_H
#define	RESULTS_H

#include <map>
#include <string>
#include <stdexcept>

#include <ModFossa/Common/ContainerTypes.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Experiment/Experiment.h>


namespace ModFossa {
    
class Results {
public:
    typedef shared_ptr<Results>::type SharedPointer;
    typedef std::map<std::string, Vector3dSharedPtr> ResultsMap3d;
    typedef std::map<std::string, Vector2dSharedPtr> ResultsMap2d;
    typedef std::map<std::string, VectorSharedPtr> ResultsMap1d;
    
    Results();
    ~Results();
    void initialize(Experiment::SharedPointer experiment);
    
    StringVec   getStateNames();
    Vector      getStateGatingVariables();
    
    Vector2d    getCurrents(std::string experiment_sweep_name);
    Vector2d    getConductances(std::string experiment_sweep_name);
    Vector2d    getVoltageProtocol(std::string experiment_sweep_name);
    Vector2d    getIV(std::string experiment_sweep_name, unsigned int time_ms);
    Vector3d    getStateProbabilities(std::string experiment_sweep_name);    
    
private:
    friend class SimulationRunner;
    Experiment::SharedPointer experiment;
    bool initialized;
    
    bool experimentSweepResultsExist(std::string name) const;
    
    void createExperimentSweepResults(
        ExperimentSweep::SharedPointer sweep, 
        Vector3dSharedPtr state_probabilities);
    
    Vector2dSharedPtr voltageProtocolAsVector2d(
        SerializedProtocolSharedPointer vp);
        
    Vector2dSharedPtr calculateCurrents(
        Vector3dSharedPtr state_probabilities, 
        Vector2dSharedPtr voltages);
    Vector2dSharedPtr calculateConductances(
            Vector3dSharedPtr state_probabilities);
        
    double reversal_potential;
    double max_conductance;
    double membrane_capacitance;
    
    StringVecSharedPtr state_names;
    VectorSharedPtr state_gating_variables;
    VectorSharedPtr voltage_protocol_steps;
    
    ResultsMap3d experiment_sweep_probabilities;
    ResultsMap2d experiment_sweep_voltage_protocol;
    ResultsMap2d experiment_sweep_currents;
    ResultsMap2d experiment_sweep_conductances;
};
}
#endif	/* RESULTS_H */

