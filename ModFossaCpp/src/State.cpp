#include <ModFossa/ModelDefinition/State.h>

using std::string;

namespace ModFossa {

State::State(string name, bool is_conducting) :
name(name),
is_conducting(is_conducting),
index(-1),
is_initial_state(false) {
    if (name.empty()) {
        throw std::runtime_error("State name cannot be empty");
    }
}

string State::getName() const {
    return name;
}

bool State::getIsConducting() const {
    return is_conducting;
}

int State::getIndex() const
{
    return index;
}
}

