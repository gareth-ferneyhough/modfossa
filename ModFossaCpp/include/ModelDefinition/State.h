#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <stdexcept>
#include <memory>

using std::string;
using std::shared_ptr;

namespace ModelDefinition {

    class State {
    public:
        typedef shared_ptr<const State> SharedPointer;

        State(string name, bool is_conducting);
        string getName() const;
        bool getIsConducting() const;

    private:
        friend class MarkovModel;

        const string name;
        const bool is_conducting;
        int index;
        bool is_initial_state;
    };
}
#endif