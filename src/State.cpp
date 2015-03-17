#include <ModFossa/ModelDefinition/State.h>

using std::string;

namespace ModFossa {

State::State(string name, bool is_conducting, double gating_variable) :
name(name),
is_conducting(is_conducting),
gating_variable(gating_variable),
index(-1),
is_initial_state(false) {
    if (name.empty()) {
        throw std::runtime_error("State name cannot be empty");
    }
    
    if (gating_variable < 0.0 || gating_variable > 1.0) {
        throw std::runtime_error("State gating variable must be between 0.0 \
                                and 1.0");
    }
    
    if(!is_conducting) {
        this->gating_variable = 0.0;
    }
}

State::~State() {
    
}

string State::getName() const {
    return name;
}

bool State::getIsConducting() const {
    return is_conducting;
}

double State::getGatingVariable() const {
    return gating_variable;
}

int State::getIndex() const
{
    return index;
}
}

