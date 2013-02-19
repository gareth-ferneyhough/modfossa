#ifndef STATE_H_
#define STATE_H_

#include <string>

using std::string;

struct State {
    State(string name, int index, bool is_conducting, bool is_initial_state) :
    name(name),
    index(index),
    is_initial_state(is_initial_state),
    is_conducting(is_conducting) {
    }

    string name;
    int index;
    bool is_initial_state;
    bool is_conducting;
};

#endif