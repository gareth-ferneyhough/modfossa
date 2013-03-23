#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <stdexcept>
#include <Common/SharedPtr.h>

using std::string;


namespace ModelDefinition {

    class State {
    public:
        typedef ModFossa::shared_ptr<State>::type SharedPointer;

        State(string name, bool is_conducting);
        string getName() const;
        bool getIsConducting() const;

    private:
        friend class MarkovModel;
        friend class TransitionMatrix;

        int getIndex() const;
        const string name;
        const bool is_conducting;
        int index;
        bool is_initial_state;
    };
}
#endif