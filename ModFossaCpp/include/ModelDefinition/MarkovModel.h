#ifndef MARKOVMODEL_H_
#define MARKOVMODEL_H_

#include <ModelDefinition/State.h>
#include <ModelDefinition/RateConstantBase.h>
#include <ModelDefinition/Connection.h>
#include <ModelDefinition/Validation/ValidationResults.h>

#include <vector>
#include <map>
#include <string>

#include <ModelDefinition/StateOfTheWorld.h>

using std::string;
using std::map;
using std::vector;

namespace ModelDefinition {

    class MarkovModel {
    public:
        typedef map<const string, RateConstantBase::SharedPointer > RateMap;
        typedef map<const string, State::SharedPointer > StateMap;
        typedef vector<Connection::SharedPointer > ConnectionsVector;

        MarkovModel();
        ~MarkovModel();

        void addState(const State::SharedPointer state);
        void addRateConstant(
                const RateConstantBase::SharedPointer rate_constant);
        void addConnection(const Connection::SharedPointer connection);
        void setInitialState(string initial_state);
        Validation::ValidationResults validate(
                const StateOfTheWorld::SharedPointer state_of_the_world);

        bool isValid() const;

    private:
        bool is_valid;
        string initial_state;

        RateMap map_of_rates;
        StateMap map_of_states;
        ConnectionsVector connections;

        bool stateExists(string name) const;
        bool rateConstantExists(string name) const;
        bool connectionExists(string from_state, string to_state) const;

        friend class TransitionMatrix;
    };
}

#endif
