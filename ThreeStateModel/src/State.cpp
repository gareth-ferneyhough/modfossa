#include <ModFossa/State.h>

State::State() :
        is_initial(false), is_conducting(false), current_probability(0) {
}

State::State(const State& rhs) :
        name(rhs.name), is_initial(rhs.is_initial), is_conducting(
                rhs.is_conducting), current_probability(
                rhs.current_probability), in_transitions(rhs.in_transitions), out_transitions(
                rhs.out_transitions) {

}
