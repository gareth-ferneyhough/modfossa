#ifndef MARKOVMODEL_H_
#define MARKOVMODEL_H_

#include <ModelDefinition/State.h>
#include <ModelDefinition/RateConstantBase.h>
#include <ModelDefinition/Connection.h>
#include <ModelDefinition/Validation/ValidationResults.h>

#include <vector>
#include <map>
#include <string>
#include <memory>

using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

namespace ModelDefinition {

	class MarkovModel {
	public:
		MarkovModel();
		~MarkovModel();

		void addState(const shared_ptr<const State> state);
		void addRateConstant(const shared_ptr<const RateConstantBase> rate_constant);
		void addConnection(const shared_ptr<const Connection> connection);
		void setInitialState(string initial_state);
		Validation::ValidationResults validate(const shared_ptr<const StateOfTheWorld> state_of_the_world);

	private:
		bool stateExists(string name) const;
		bool rateConstantExists(string name) const;
		bool connectionExists(string from_state, string to_state) const;

		map<const string, shared_ptr<const RateConstantBase>> map_of_rates;
		map<const string, shared_ptr<const State>> map_of_states;
		vector<shared_ptr<const Connection>> connections;

		string initial_state;

		//shared_ptr<ConnectionManager> connectionManager;
	};
}

#endif
