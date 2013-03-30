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
#include <ModFossa/Experiment/ExperimentSweep.h>


namespace ModFossa {
    
class Results {
public:
    typedef shared_ptr<Results>::type SharedPointer;
    typedef std::map<std::string, Vector3d> ResultsMap3d;
    typedef std::map<std::string, Vector2d> ResultsMap2d;
    
    Results();
    ~Results();
    
    Vector      getIV(std::string experiment_sweep_name);
    Vector2d    getCurrents(std::string experiment_sweep_name);
    Vector2d    getVoltageProtocol(std::string experiment_sweep_name);
    Vector3d    getStateProbabilities(std::string experiment_sweep_name);    
    
private:
    friend class SimulationRunner;
    
    bool experimentSweepResultsExist(std::string name) const;
    
    void saveExperimentSweepProbabilities(ExperimentSweep::SharedPointer sweep, 
        Vector3d state_probabilities);
    
    ResultsMap3d experiment_sweep_probabilities;
    ResultsMap2d experiment_sweep_voltage_protocol;

};
}
#endif	/* RESULTS_H */

