#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/RateConstantBase.h>
#include <ModelDefinition/Validation/ValidationResults.h>

#include <stdexcept>

namespace ModelDefinition {

    MarkovModel::MarkovModel() {
        //map_of_rates = shared_ptr(new map<string, const RateConstantBase*>();
        //map_of_states = new map<string, const State*>();
        //connections = new vector<Connection*>();
    }

    MarkovModel::~MarkovModel() {
        //delete map_of_rates;
        //delete map_of_states;
        //delete connections;
    }

    void MarkovModel::addState(string name, bool conducting, bool initial) {
        if (name.empty()) {
			throw std::runtime_error("name cannot be empty");
        }

        if (stateExists(name)) {
            throw std::runtime_error(
                    "state with same name already exists");
        }

        int index = -1;
        map_of_states[name] = shared_ptr<State>(new State(name, index, conducting, initial));
    }

    void MarkovModel::addRateConstant(const shared_ptr<const RateConstantBase>rate_constant) {
        string name = rate_constant->getName();
        if (rateConstantExists(name)) {
            throw std::runtime_error(
                    "RateConstant with same name already exists");
        }

        map_of_rates[name] = rate_constant;
    }

    void MarkovModel::addConnection(string from_state, string to_state,
            string rate_name) {
        connections.push_back(shared_ptr<Connection>(
			new Connection(from_state, to_state, rate_name)));
    }

    bool MarkovModel::stateExists(string name) {
        map<const string, shared_ptr<const State>>::const_iterator it;
        it = map_of_states.find(name);

        if (it != map_of_states.end()) {
            return true;
        }
        return false;
    }

    bool MarkovModel::rateConstantExists(string name) {
        map<const string, shared_ptr<const RateConstantBase>>::const_iterator it;
        it = map_of_rates.find(name);

        if (it != map_of_rates.end()) {
            return true;
        }
        return false;
    }

    void MarkovModel::setInitialState(string initial_state) {
        if (initial_state.empty()) {
            throw std::runtime_error("initial_state name cannot be empty");
        }
        this->initial_state = initial_state;
    }

    Validation::ValidationResults MarkovModel::validate() {
        using namespace Validation; // this stinks

        vector< std::pair<ErrorType, string > > errors;
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
        for (int i = 0; i < connections.size(); ++i) {

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
        
        // TODO: Check that each LigandGated rate constant has its ligand defined in 
        // state of the world

        ValidationResults results(error_level, errors);
        return results;
    }
}