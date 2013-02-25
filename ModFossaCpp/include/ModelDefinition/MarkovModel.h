#ifndef MARKOVMODEL_H_
#define MARKOVMODEL_H_

#include <ModelDefinition/State.h>
#include <ModelDefinition/Connection.h>
#include <ModelDefinition/Validation/ValidationResults.h>

#include <vector>
#include <map>
#include <string>

using std::string;
using std::map;
using std::vector;

namespace ModelDefinition {
    
class State;
class Connection;
class RateConstantBase;
class ConnectionManager;

/**
 * Class responsible for creating and storing information required to
 * describe a markov model for an ion channel. The user adds RateConstants
 * and States using the methods provided. After the model is described,
 * the user calls BuildConnections(). At this point the ConnectionManager and 
 * ModelDescription are used to create the transitionMatrix, which is 
 * used to run the simulation.
 */

    class MarkovModel {
    public:
        MarkovModel();
        ~MarkovModel();

        void addState(string name, bool conducting, bool initial = false);
        void addRateConstant(const RateConstantBase& rate_constant);
        void addConnection(string from_state, string to_state,
                string rate_constant);
        void setInitialState(string initial_state);
        Validation::ValidationResults validate();

    private:
        bool stateExists(string name);
        bool rateConstantExists(string name);

        map<string, const RateConstantBase*>* map_of_rates;
        map<string, const State*>* map_of_states;
        vector<Connection*>* connections;

        string initial_state;

        ConnectionManager* connectionManager;
    };
}

#endif
