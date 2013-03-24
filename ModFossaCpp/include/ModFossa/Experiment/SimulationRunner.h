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

namespace ModFossa {
class SimulationRunner {
public:
    SimulationRunner();
    ~SimulationRunner();

    void runAllExperimentSweeps(Experiment);
    void runExperimentSweep(std::string experiment_sweep_name);
private:
    Experiment experiment;

};
}

#endif	/* SIMULATIONRUNNER_H */

