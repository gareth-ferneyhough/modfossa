#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <string>
using std::string;

struct Connection {
    Connection(string from_state, string to_state, string rate_name) :
    from_state(from_state),
    to_state(to_state),
    rate_name(rate_name) {
    }

    string from_state;
    string to_state;
    string rate_name;
};
#endif
