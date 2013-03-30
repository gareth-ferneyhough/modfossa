/* 
 * File:   Results.cpp
 * Author: gareth
 * 
 * Created on March 29, 2013, 9:22 PM
 */

#include <ModFossa/Results/Results.h>

namespace ModFossa {
Results::Results() {
}

Results::~Results() {
}

Vector3d Results::getStateProbabilities(std::string name) {

    if (name.empty()) {
        throw std::runtime_error("Experiment sweep name cannot be empty");
    }
    
    if (!experimentSweepResultsExist(name)) {
        throw std::runtime_error(
                "ExperimentSweep results " + name + " does not exist");
    }
    return experiment_sweep_probabilities[name];
}


bool Results::experimentSweepResultsExist(std::string name) const {
    ResultsMap::const_iterator it;
    it = experiment_sweep_probabilities.find(name);

    if (it != experiment_sweep_probabilities.end()) {
        return true;
    }
    return false;
}

void Results::saveExperimentSweepProbabilities(std::string experimentSweepName, 
    Vector3d state_probabilities) {
    
    if(experimentSweepResultsExist(experimentSweepName)) {
        throw std::runtime_error("Experiment Sweep " + experimentSweepName + \
                " already has results saved");
    }
    
    experiment_sweep_probabilities[experimentSweepName] = state_probabilities;    
}

}
