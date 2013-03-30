#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <stdexcept>
#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {

class State {
public:
    typedef ModFossa::shared_ptr<State>::type SharedPointer;

    State(std::string name, bool is_conducting, double gating_variable = 1.0);
    ~State();
    
    std::string getName() const;
    bool getIsConducting() const;
    double getGatingVariable() const;

private:
    friend class MarkovModel;
    friend class TransitionMatrix;

    int getIndex() const;
    const std::string name;
    const bool is_conducting;
    const double gating_variable;
    int index;
    bool is_initial_state;
};
}
#endif