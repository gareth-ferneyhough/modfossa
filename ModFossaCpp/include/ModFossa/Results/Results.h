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


namespace ModFossa {
    
class Results {
public:
    typedef shared_ptr<Results>::type SharedPointer;
    typedef std::map<std::string, Vector3d> ResultsMap;
    
    Results();
    ~Results();
    
    Vector      getIV(std::string experiment_sweep_name);
    Vector2d    getCurrents(std::string experiment_sweep_name);
    Vector2d    getVoltageProtocol(std::string experiment_sweep_name);
    Vector3d    getStateProbabilities(std::string experiment_sweep_name);    
    
private:
    friend class SimulationRunner;
    
    bool experimentSweepResultsExist(std::string name) const;
    
    void saveExperimentSweepProbabilities(std::string experimentSweepName, 
    Vector3d state_probabilities);
    
    ResultsMap experiment_sweep_probabilities;

};
}
#endif	/* RESULTS_H */

