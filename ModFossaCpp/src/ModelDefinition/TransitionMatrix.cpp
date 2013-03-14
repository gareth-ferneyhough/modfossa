/* 
 * File:   TransitionMatrix.cpp
 * Author: gareth
 * 
 * Created on March 11, 2013, 5:01 PM
 */

#include <ModelDefinition/TransitionMatrix.h>

namespace ModelDefinition {

    TransitionMatrix::TransitionMatrix() {
    }

    TransitionMatrix::TransitionMatrix(const TransitionMatrix& orig) {
    }

    TransitionMatrix::~TransitionMatrix() {
    }

    void TransitionMatrix::update() {

    }

    void TransitionMatrix::create(const MarkovModel& markov_model) {

        if (!markov_model.isValid()) {
            throw std::runtime_error(
                    "Fatal error: Attempting to create TransitionMatrix with unvalidated MarkovModel");
        }

        // Create the intermediate 3d transitions matrix of size NxN, where
        // N is the number of states.
        const int matrix_size = markov_model.map_of_states.size();
        transitions_3d.resize(matrix_size);
        for (int i = 0; i < matrix_size; ++i) {
            transitions_3d[i].resize(matrix_size);
        }

        std::cout << "matrix size: " << matrix_size;

        // Iterate through our connections and add two Transition entries
        // to the intermediate 3d transitions matrix for each connection in the
        // model. 
        MarkovModel::ConnectionsVector::const_iterator it;
        for (it = markov_model.connections.begin();
                it != markov_model.connections.end(); ++it) {

            string from_state_name = (*it)->from_state;
            string to_state_name = (*it)->to_state;
            string rate_name = (*it)->rate_name;

            State::SharedPointer from_state =
                    findState(from_state_name, markov_model.map_of_states);
            State::SharedPointer to_state =
                    findState(to_state_name, markov_model.map_of_states);
            RateConstantBase::SharedPointer rate =
                    findRate(rate_name, markov_model.map_of_rates);

            // We need the indices that MarkovModel assigned to each state.
            // These will be the indices to the matrix.
            int outgoing_index = from_state->getIndex();
            int incoming_index = to_state->getIndex();

            // Add the transition to the appropriate position in the matrix 
            // with a negative sign
            transitions_3d[outgoing_index][incoming_index].push_back(
                    Transition::SharedPointer(new Transition(rate, false)));

            // Add the reversed transition to the matrix with a positive sign
            transitions_3d[incoming_index][outgoing_index].push_back(
                    Transition::SharedPointer(new Transition(rate, true)));
        }
    }

    mat TransitionMatrix::get() const {
        return transition_matrix;
    }

    RateConstantBase::SharedPointer TransitionMatrix::findRate(string rate_name,
            const MarkovModel::RateMap& rates) const {

        MarkovModel::RateMap::const_iterator rate_iterator =
                rates.find(rate_name);

        // This should never happen; this should only be called if MarkovModel
        // is valid.
        if (rate_iterator == rates.end()) {
            throw std::runtime_error(
                    "Fatal error: " + rate_name + " not found in map_of_rates");
        }

        return rate_iterator->second;
    }

    State::SharedPointer TransitionMatrix::findState(string state_name,
            const MarkovModel::StateMap& states) const {

        MarkovModel::StateMap::const_iterator state_iterator =
                states.find(state_name);

        // This should never happen; this should only be called if MarkovModel
        // is valid.
        if (state_iterator == states.end()) {
            throw std::runtime_error(
                    "Fatal error: " + state_name + " not found in map_of_states");
        }

        return state_iterator->second;
    }
}
