#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <stdexcept>

using std::string;

namespace ModelDefinition {

    struct State {

        State(string name, bool is_conducting) :
        name(name),
        is_conducting(is_conducting),
		index(-1),
		is_initial_state(false) {
			if(name.empty()) {
				throw std::runtime_error("State name cannot be empty");
			}
        }

        string name;
		bool is_conducting;
        
	protected:
		int index;
        bool is_initial_state;
    };
}

#endif