#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <stdexcept>
#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {

class State {
public:
    typedef ModFossa::shared_ptr<State>::type SharedPointer;

    State(std::string name, bool is_conducting);
    std::string getName() const;
    bool getIsConducting() const;

private:
    friend class MarkovModel;
    friend class TransitionMatrix;

    int getIndex() const;
    const std::string name;
    const bool is_conducting;
    int index;
    bool is_initial_state;
};
}
#endif