/* 
 * File:   SimulationRunner.h
 * Author: gareth
 *
 * Created on March 23, 2013, 9:23 PM
 */

#ifndef SIMULATIONRUNNER_H
#define	SIMULATIONRUNNER_H


#include <string>
#include <ModFossa/Experiment/Experiment.h>
#include <ModFossa/Experiment/Simulator.h>

namespace ModFossa {
class SimulationRunner {
public:
    SimulationRunner();
    ~SimulationRunner();
    
    Experiment::SharedPointer getExperiment() const;
    
    void runAllExperimentSweeps();
    void runExperimentSweep(std::string experiment_sweep_name);
    
private:
    Experiment::SharedPointer experiment;
    Simulator::SharedPointer simulator;

    /**
     * Initialize the Experiment and Simulator classes.
     */
    void initialize();
};
}

#endif	/* SIMULATIONRUNNER_H */

