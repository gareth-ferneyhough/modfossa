/* 
 * File:   Results.cpp
 * Author: gareth
 * 
 * Created on March 29, 2013, 9:22 PM
 */

#include <ModFossa/Results/Results.h>
#include <cassert>

namespace ModFossa {

    Results::Results() :
    initialized(false) {
    }

    Results::~Results() {
    }

    /**
     * Get relevant information from the Experiment class required to calculate
     * the results structures. 
     * 
     * @param experiment SharedPointer to the Experiment class.
     */
    void Results::initialize(Experiment::SharedPointer experiment) {
        assert(initialized == false);
        initialized = true;

        MarkovModel::SharedPointer markov_model = experiment->getMarkovModel();
        state_names = markov_model->getStateNames();
        state_gating_variables = markov_model->getStateGatingVariables();
        max_conductance = markov_model->getMaxChannelConductance();
        reversal_potential = markov_model->getReversalPotential();
    }

    StringVec Results::getStateNames() {
        if (!initialized) {
            throw std::runtime_error("Simulation must be run before \
                                retrieving results");
        }
        return *state_names;
    }

    Vector Results::getStateGatingVariables() {
        if (!initialized) {
            throw std::runtime_error("Simulation must be run before \
                                retrieving results");
        }
        return *state_gating_variables;
    }

    Vector3d Results::getStateProbabilities(std::string name) {

        if (name.empty()) {
            throw std::runtime_error("Experiment sweep name cannot be empty");
        }

        if (!experimentSweepResultsExist(name)) {
            throw std::runtime_error(
                    "ExperimentSweep results " + name + " do not exist");
        }
        return *(experiment_sweep_probabilities[name]);
    }
    
    Vector2d Results::getCurrents(std::string name) {

        if (name.empty()) {
            throw std::runtime_error("Experiment sweep name cannot be empty");
        }

        if (!experimentSweepResultsExist(name)) {
            throw std::runtime_error(
                    "ExperimentSweep results " + name + " do not exist");
        }
        return *(experiment_sweep_currents[name]);
    }

    Vector2d Results::getVoltageProtocol(
            std::string experiment_sweep_name) {

        if (experiment_sweep_name.empty()) {
            throw std::runtime_error("Experiment sweep name cannot be empty");
        }

        if (!experimentSweepResultsExist(experiment_sweep_name)) {
            throw std::runtime_error(
                    "ExperimentSweep results " + experiment_sweep_name \
                + " do not exist");
        }
        return *(experiment_sweep_voltage_protocol[experiment_sweep_name]);
    }

    bool Results::experimentSweepResultsExist(std::string name) const {
        ResultsMap3d::const_iterator it;
        it = experiment_sweep_probabilities.find(name);

        if (it != experiment_sweep_probabilities.end()) {
            return true;
        }
        return false;
    }

    void Results::createExperimentSweepResults(
            ExperimentSweep::SharedPointer sweep,
            Vector3dSharedPtr state_probabilities) {

        assert(initialized == true);

        std::string experiment_sweep_name = sweep->getName();

        if (experimentSweepResultsExist(experiment_sweep_name)) {
            throw std::runtime_error("Experiment Sweep " + experiment_sweep_name + \
                " already has results saved");
        }

        // Save the state probabilities
        experiment_sweep_probabilities[experiment_sweep_name] = state_probabilities;

        // Transform and save the voltage protocol as a 2d vector
        SerializedProtocolSharedPointer vp = sweep->getSerializedVoltageProtocol();
        Vector2dSharedPtr voltage_protocol = voltageProtocolAsVector2d(vp);
        experiment_sweep_voltage_protocol[experiment_sweep_name] = voltage_protocol;

        // Calculate the currents
        experiment_sweep_currents[experiment_sweep_name] =
                calculateCurrents(state_probabilities, voltage_protocol);
    }

    Vector2dSharedPtr Results::calculateCurrents(
            Vector3dSharedPtr state_probabilities,
            Vector2dSharedPtr voltages) {

        Vector2dSharedPtr currents(new Vector2d());

        unsigned int number_of_protocol_iterations = state_probabilities->size();
        unsigned int number_of_time_steps = state_probabilities->front().size();
        unsigned int number_of_states = state_probabilities->front().front().size();
        
        assert(voltages->size() == number_of_protocol_iterations);
        assert(voltages->front().size() == number_of_time_steps);

        for (unsigned int protocol_iteration_index = 0;
                protocol_iteration_index < number_of_protocol_iterations;
                ++protocol_iteration_index) {

            currents->push_back(Vector());

            for (unsigned int time_index = 0;
                    time_index < number_of_time_steps;
                    ++time_index) {

                Vector state_probs =
                        (*state_probabilities)[protocol_iteration_index][time_index];
                double voltage = (*voltages)[protocol_iteration_index][time_index];
                double current = 0;

                for (unsigned int state_index = 0;
                        state_index < number_of_states;
                        ++state_index) {

                    current += state_probs[state_index] *
                            (*state_gating_variables)[state_index];
                }
                current *= max_conductance * (voltage - reversal_potential);
                currents->back().push_back(current);
            }
        }
        return currents;
    }

    Vector2dSharedPtr Results::voltageProtocolAsVector2d(
            SerializedProtocolSharedPointer vp) {

        Vector2dSharedPtr voltage_protocol(new Vector2d());

        SerializedProtocol::iterator protocol_iterator;
        for (protocol_iterator = vp->begin();
                protocol_iterator != vp->end();
                ++protocol_iterator) {

            voltage_protocol->push_back(Vector());
            int voltage_protocol_iteration_time_step = 0; // ms

            for (unsigned int inner_index = 0;
                    inner_index < protocol_iterator->size();
                    ++inner_index) {

                double voltage = ((*protocol_iterator)[inner_index]).second;

                int change_time_index;
                // We are currently at the last protocol stage
                if (inner_index == protocol_iterator->size() - 1) {
                    change_time_index = inner_index;
                } else {
                    change_time_index = inner_index + 1;
                }

                double voltage_change_time =
                        ((*protocol_iterator)[change_time_index]).first;

                while (voltage_protocol_iteration_time_step !=
                        voltage_change_time) {

                    voltage_protocol->back().push_back(voltage);
                    voltage_protocol_iteration_time_step++;
                }
            }
        }
        return voltage_protocol;
    }


}
