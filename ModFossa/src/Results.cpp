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
        this->experiment = experiment;
        state_names = markov_model->getStateNames();
        state_gating_variables = markov_model->getStateGatingVariables();
        max_conductance = markov_model->getMaxChannelConductance();
        reversal_potential = markov_model->getReversalPotential();
        membrane_capacitance =  markov_model->getMembraneCapacitance();
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
    
    Vector2d Results::getConductances(std::string name) {

        if (name.empty()) {
            throw std::runtime_error("Experiment sweep name cannot be empty");
        }

        if (!experimentSweepResultsExist(name)) {
            throw std::runtime_error(
                    "ExperimentSweep results " + name + " do not exist");
        }
        return *(experiment_sweep_conductances[name]);
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
        
        // Save the voltage protocol steps, used to calculate the IV curve
        voltage_protocol_steps = 
                experiment->getVoltageProtocol(
                sweep->getVoltageProtocolName())->getVoltageProtocolSteps();

        /**
         * @todo Combine calculateConductances and calculateCurrents
         */
        
        // Calculate the currents
        experiment_sweep_currents[experiment_sweep_name] =
                calculateCurrents(state_probabilities, voltage_protocol);
        
        // Calculate the conductances
        experiment_sweep_conductances[experiment_sweep_name] =
                calculateConductances(state_probabilities);
    }

    Vector2dSharedPtr Results::calculateConductances(
            Vector3dSharedPtr state_probabilities) {

        Vector2dSharedPtr conductances(new Vector2d());

        unsigned int number_of_protocol_iterations = state_probabilities->size();
        unsigned int number_of_time_steps = state_probabilities->front().size();
        unsigned int number_of_states = state_probabilities->front().front().size();
       
        for (unsigned int protocol_iteration_index = 0;
                protocol_iteration_index < number_of_protocol_iterations;
                ++protocol_iteration_index) {

            conductances->push_back(Vector());

            for (unsigned int time_index = 0;
                    time_index < number_of_time_steps;
                    ++time_index) {

                Vector state_probs =
                        (*state_probabilities)[protocol_iteration_index][time_index];
                double conductance = 0;

                for (unsigned int state_index = 0;
                        state_index < number_of_states;
                        ++state_index) {

                    conductance += state_probs[state_index] *
                            (*state_gating_variables)[state_index];
                }
                conductance *= max_conductance;
                conductances->back().push_back(conductance);
            }
        }
        return conductances;
    }
    
    /**
     * Calculate the currents for an experiment sweep given a 3d vector of 
     * state probabilities, and a 2d vector of voltages. Other values used 
     * are: maximum conductance, reversal potential, and channel gating values.
     * 
     * @todo This needs to be vectorized.
     * 
     * @param state_probabilities
     * @param voltages
     * @return 
     */
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

    /**
     * Convert the serialized voltage protocol into a more usable form for 
     * plotting and calculating currents.
     * 
     * @todo Would be nice if this was returned from the Simulator so that
     * we didn't have to do extra work here to create it.
     */
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
    
    /**
     * Calculate the IV curve for an experiment sweep at the given time in 
     * milliseconds. The units on the vertical axis are pA/pF. The 
     * horizontal axis is milliVolts.
     * 
     * @param experiment_sweep_name
     * @param time_ms Time in milliseconds at which to calculate the IV curve.
     * @return 
     */
    Vector2d Results::getIV(std::string experiment_sweep_name, 
            unsigned int time_ms) {
        
        if (experiment_sweep_name.empty()) {
            throw std::runtime_error("Experiment sweep name cannot be empty");
        }

        if (!experimentSweepResultsExist(experiment_sweep_name)) {
            throw std::runtime_error(
                    "ExperimentSweep results " + experiment_sweep_name \
                + " do not exist");
        }
        
        if(voltage_protocol_steps->size() == 0) {
            throw std::runtime_error("Cannot create IV curve because the "\
                                     "voltage protocol has no stepped stage");
        }
        
        Vector2dSharedPtr currents = 
                experiment_sweep_currents[experiment_sweep_name];
        
        // Make sure our current and voltage data are the same dimensions.        
        unsigned int number_voltage_steps = voltage_protocol_steps->size();
        unsigned int number_time_steps = (*currents)[0].size();
             
        assert(currents->size() == number_voltage_steps);
                
        // Make sure that user's time value is within range.
        if(time_ms < 0 || time_ms >= number_time_steps) {
            throw std::runtime_error("Requested time value for IV curve is "\
                                    "outside of the range for the given "\
                                    "experiment sweep");
        }
        
        Vector2d iv_curve;
        iv_curve.push_back(Vector()); // voltages
        iv_curve.push_back(Vector()); // currents
        
        for(unsigned int voltage_step_index = 0; 
                voltage_step_index < number_voltage_steps; 
                ++ voltage_step_index) {
            
            iv_curve[0].push_back((*voltage_protocol_steps)[voltage_step_index]);
            iv_curve[1].push_back((*currents)[voltage_step_index][time_ms]); 
        }
        return iv_curve;
    }
}
