/* 
 * File:   HelperFunctions.cpp
 * Author: gareth
 * 
 * Created on March 13, 2013, 10:49 PM
 */

#include <ModelDefinition/HelperFunctions.h>
#include <stdexcept>

namespace ModelDefinition {

    RateConstantBase::SharedPointer findRate(string rate_name,
            const MarkovModel::RateMap& rates) {

        MarkovModel::RateMap::const_iterator rate_iterator =
                rates.find(rate_name);

        // This should never happen; this should only be called if MarkovModel
        // is valid.
        if (rate_iterator == rates.end()) {
            throw std::runtime_error(
                    "RateConstant with " + rate_name + " not found");
        }
        return rate_iterator->second;
    }

    State::SharedPointer findState(string state_name,
            const MarkovModel::StateMap& states) {

        MarkovModel::StateMap::const_iterator state_iterator =
                states.find(state_name);

        // This should never happen; this should only be called if MarkovModel
        // is valid.
        if (state_iterator == states.end()) {
            throw std::runtime_error(
                    "State with " + state_name + " not found");
        }

        return state_iterator->second;
    }
}

