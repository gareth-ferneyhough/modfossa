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
#include <vector>

#include <ModFossa/Common/ContainerTypes.h>
#include <ModFossa/Common/TransitionMatrix.h>
#include <ModFossa/Experiment/Experiment.h>
#include <ModFossa/Experiment/Simulator.h>
#include <ModFossa/Results/Results.h>

namespace ModFossa {

    class SimulationRunner {
    public:        

        SimulationRunner();
        ~SimulationRunner();

        Experiment::SharedPointer getExperiment() const;
        Results::SharedPointer getResultsClass() const;
        
        void runAllExperimentSweeps(bool start_at_steady_state = true);

    private:
        Experiment::SharedPointer experiment;
        Simulator::SharedPointer simulator;
        Results::SharedPointer results;
        
        bool simulation_has_been_run;

        /**
         * Initialize the Experiment and Simulator classes.
         */
        void initialize();
        
        void doRunExperimentSweep(ExperimentSweep::SharedPointer sweep,
                bool start_at_steady_state = true);
    };
}

#endif	/* SIMULATIONRUNNER_H */

