#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/RateConstantBase.h>
#include <ModelDefinition/Validation/ValidationResults.h>

#include <boost/log/trivial.hpp>
#include <stdexcept>

namespace ModelDefinition {

    MarkovModel::MarkovModel() {
        map_of_rates = new map<string, const RateConstantBase*>();
        map_of_states = new map<string, const State*>();
        connections = new vector<const Connection*>();
    }

    MarkovModel::~MarkovModel() {
        delete map_of_rates;
        delete map_of_states;
        delete connections;
    }

    void MarkovModel::addState(string name, bool conducting, bool initial) {
        if (name.empty()) {
            throw std::runtime_error("name cannot be empty");
        }

        if (stateAlreadyExists(name)) {
            throw std::runtime_error(
                    "state with same name already exists");
        }

        int index = -1;
        (*map_of_states)[name] = new State(name, index, conducting, initial);
    }

    void MarkovModel::addRateConstant(const RateConstantBase& rate_constant) {
        string name = rate_constant.getName();
        if (rateConstantAlreadyExists(name)) {
            throw std::runtime_error(
                    "RateConstant with same name already exists");
        }

        (*map_of_rates)[name] = &rate_constant;
    }

    void MarkovModel::addConnection(string from_state, string to_state,
            string rate_name) {
        connections->push_back(new Connection(from_state, to_state, rate_name));
    }

    bool MarkovModel::stateAlreadyExists(string name) {
        map<string, const State*>::const_iterator it;
        it = map_of_states->find(name);

        if (it != map_of_states->end()) {
            return true;
        }
        return false;
    }

    bool MarkovModel::rateConstantAlreadyExists(string name) {
        map<string, const RateConstantBase*>::const_iterator it;
        it = map_of_rates->find(name);

        if (it != map_of_rates->end()) {
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
        //using Validation::ErrorLevel;
        //using Validation::ErrorType;
        //using Validation::ValidationResults;
        using namespace Validation;
        
        vector< std::pair<ErrorType, string > > errors;
        ErrorLevel error_level;
        
        if(initial_state.empty()) {
            errors.push_back(std::make_pair(
            INITIAL_STATE_NOT_DEFINED, "Initial state not defined"));
            
            error_level = ERRORS;
        }
        
        ValidationResults results(error_level, errors);
        return results;
    }
}