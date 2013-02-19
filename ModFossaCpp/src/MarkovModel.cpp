#include <MarkovModel.h>
#include <RateConstantBase.h>
#include <stdexcept>

MarkovModel::MarkovModel() {
    map_of_rates = new map<string, const RateConstantBase*>();
    map_of_states = new map<string, State*>();
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
    map<string, State*>::const_iterator it;
    it = map_of_states->find(name);
    if (it != map_of_states->end()) {
        return true;
    }
}

bool MarkovModel::rateConstantAlreadyExists(string name) {
    map<string, const RateConstantBase*>::const_iterator it;
    it = map_of_rates->find(name);
    if (it != map_of_rates->end()) {
        return true;
    }
}

void MarkovModel::setInitialState(string initial_state) {
    if (initial_state.empty()) {
        throw std::runtime_error("initial_state name cannot be empty");
    }
    this->initial_state = initial_state;
}

void validate()
{
    // initial_state
}