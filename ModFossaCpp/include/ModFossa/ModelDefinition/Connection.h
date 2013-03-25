#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <string>
#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {

struct Connection {
    typedef ModFossa::shared_ptr<Connection>::type SharedPointer;
    Connection(
        std::string from_state, 
        std::string to_state, 
        std::string rate_name) :
    from_state(from_state),
    to_state(to_state),
    rate_name(rate_name) {
    }

    std::string from_state;
    std::string to_state;
    std::string rate_name;
};
}
#endif
