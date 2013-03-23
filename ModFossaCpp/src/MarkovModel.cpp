#include <stdexcept>

#include <ModFossa/ModelDefinition/MarkovModel.h>
#include <ModFossa/ModelDefinition/RateConstantBase.h>
#include <ModFossa/ModelDefinition/Validation/ValidationResults.h>

using std::string;
using std::vector;

namespace ModFossa {

MarkovModel::MarkovModel() :
is_valid(false) {
}

MarkovModel::~MarkovModel() {
}

void MarkovModel::addState(const State::SharedPointer state) {
    string name = state->name;
    if (stateExists(name)) {
        throw std::runtime_error(
                "State with name " + name + " already exists");
    }

    map_of_states[name] = state;
    is_valid = false;
}

void MarkovModel::addRateConstant(const RateConstantBase::SharedPointer
rate_constant) {
    string name = rate_constant->getName();
    if (rateConstantExists(name)) {
        throw std::runtime_error(
                "RateConstant with name " + name + " already exists");
    }

    map_of_rates[name] = rate_constant;
    is_valid = false;
}

void MarkovModel::addConnection(const Connection::SharedPointer connection) {
    if (connectionExists(connection->from_state, connection->to_state)) {
        throw std::runtime_error(
                "Connection from " + connection->from_state + " to " +
                connection->to_state + " already exists");
    }

    connections.push_back(connection);
    is_valid = false;
}

bool MarkovModel::stateExists(string name) const {
    StateMap::const_iterator it;
    it = map_of_states.find(name);

    if (it != map_of_states.end()) {
        return true;
    }
    return false;
}

bool MarkovModel::rateConstantExists(string name) const {
    RateMap::const_iterator it;
    it = map_of_rates.find(name);

    if (it != map_of_rates.end()) {
        return true;
    }
    return false;
}

bool MarkovModel::connectionExists(string from_state, string to_state) const {
    ConnectionsVector::const_iterator it;
    bool found = false;
    it = connections.begin();

    while (!found && it != connections.end()) {
        if ((*it)->from_state == from_state && (*it)->to_state == to_state) {
            found = true;
        }
        ++it;
    }
    return found;
}

void MarkovModel::setInitialState(string initial_state) {
    if (!this->initial_state.empty()) {
        throw std::runtime_error("initial_state already set to " + this->initial_state);
    }

    if (initial_state.empty()) {
        throw std::runtime_error("initial_state name cannot be empty");
    }

    this->initial_state = initial_state;
    is_valid = false;
}

bool MarkovModel::isValid() const {
    return is_valid;
}

/*
 * Checks that the model is valid and assigns indices to all of the states.
 * If errors are detected, the error_level is set to ERRORS and the error
 * is appended to the vector of errors, and returned in the
 * ValidationResults structure.
 */
Validation::ValidationResults MarkovModel::validate(
        const StateOfTheWorld::SharedPointer state_of_the_world) {
    using namespace Validation;

    vector < std::pair<ErrorType, string >> errors;
    ErrorLevel error_level = NO_WARNINGS;

    // initial_state has been defined?
    if (initial_state.empty()) {
        errors.push_back(std::make_pair(
                INITIAL_STATE_NOT_DEFINED, "Initial state not defined"));

        error_level = ERRORS;
    }

    // at least one connection?
    if (connections.size() == 0) {
        errors.push_back(std::make_pair(
                NO_CONNECTIONS, "No connections defined"));

        error_level = ERRORS;
    }

    // check connections that rate_constants and states exist
    for (unsigned int i = 0; i < connections.size(); ++i) {

        string from_state = connections[i]->from_state;
        string to_state = connections[i]->to_state;
        string rate_name = connections[i]->rate_name;

        if (!stateExists(from_state)) {
            errors.push_back(std::make_pair(
                    STATE_NOT_DEFINED,
                    "State not defined: " + from_state));

            error_level = ERRORS;
        }

        if (!stateExists(to_state)) {
            errors.push_back(std::make_pair(
                    STATE_NOT_DEFINED,
                    "State not defined: " + to_state));

            error_level = ERRORS;
        }

        if (!rateConstantExists(rate_name)) {
            errors.push_back(std::make_pair(
                    RATE_CONSTANT_NOT_DEFINED,
                    "Rate constant not defined: " + rate_name));

            error_level = ERRORS;
        }
    }

    if (state_of_the_world == NULL) {
        errors.push_back(std::make_pair(
                STATE_OF_THE_WORLD_IS_NULL,
                "state_of_the_world cannot be NULL"));

        error_level = ERRORS;
    }

    // TODO: Add warnings for unused states and rates.

    if (state_of_the_world != NULL) {
        // Check that each LigandGated rate constant has its ligand 
        // defined in state_of_the_world
        RateMap::const_iterator it;
        for (it = map_of_rates.begin(); it != map_of_rates.end(); ++it) {
            try {
                it->second->getRate(state_of_the_world);
            } catch (std::runtime_error& e) {
                errors.push_back(std::make_pair(
                        LIGAND_NOT_DEFINED,
                        // This is a bad and ugly message!
                        "Ligand not defined: " + string(e.what())));

                error_level = ERRORS;
            }
        }
    }

    /* If everything is valid, set the validation flag so that no changes
     * can be made without re-validating. Also, we need to assign indices 
     * to all the states. Both of the transition matrices will be size NxN, 
     * where N is the number of states. State with index 0 will occupy the 
     * 0th row and column of the matrices.   
     * 
     * Also, assign the initial_state flag to the state which was 
     * designated so.
     */
    if (error_level != ERRORS) {
        StateMap::iterator it;
        int index = 0;
        for (it = map_of_states.begin(); it != map_of_states.end(); ++it) {
            it->second->index = index;
            ++index;

            if (it->first == initial_state) {
                it->second->is_initial_state = true;
            }
        }
        is_valid = true;
    }

    ValidationResults results(error_level, errors);
    return results;
}
}