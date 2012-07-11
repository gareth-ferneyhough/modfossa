/*
 * State.h
 *
 *  Created on: Jul 10, 2012
 *      Author: gareth
 */

#include <vector>
#include <ModFossa/Transition.h>

class State {
public:
    State();
    State(const State&);

    StateName name;
    bool is_initial;
    bool is_conducting;
    double current_probability;

    std::vector<Transition> in_transitions;
    std::vector<Transition> out_transitions;
};
