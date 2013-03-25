/* 
 * File:   SimulationRunner.h
 * Author: gareth
 *
 * Created on March 23, 2013, 9:23 PM
 */

#ifndef SIMULATIONRUNNER_H
#define	SIMULATIONRUNNER_H


#include <string>
#include <map>

#include <ModFossa/Common/TransitionMatrix.h>
#include <ModFossa/Experiment/Experiment.h>
#include <ModFossa/Experiment/Simulator.h>

namespace ModFossa {
class SimulationRunner {
public:
    typedef std::map<std::string, ExperimentSweepResults> ResultsMap;
    
    SimulationRunner();
    ~SimulationRunner();
    
    Experiment::SharedPointer getExperiment() const;
    
    void runAllExperimentSweeps();
    void runExperimentSweep(std::string experiment_sweep_name);
    
    // test
    std::string getVersion() { return version; }
    // test
    
private:
    const std::string version = "0.1";
    Experiment::SharedPointer experiment;
    Simulator::SharedPointer simulator;
    ResultsMap results_map;

    /**
     * Initialize the Experiment and Simulator classes.
     */
    void initialize();
};
}

#endif	/* SIMULATIONRUNNER_H */

