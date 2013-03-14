/* 
 * File:   HelperFunctions.h
 * Author: gareth
 *
 * Created on March 13, 2013, 10:49 PM
 */

#ifndef HELPERFUNCTIONS_H
#define	HELPERFUNCTIONS_H

#include <ModelDefinition/MarkovModel.h>

namespace ModelDefinition {

    /* Finds rate with given name in the map.
     * If the rate does not exist, an exception is thrown.
     */
    RateConstantBase::SharedPointer findRate(string rate_name,
            const MarkovModel::RateMap& rate_map);

    /* Finds rate with given name in the map.
     * If the rate does not exist, an exception is thrown.
     */
    State::SharedPointer findState(string state_name,
            const MarkovModel::StateMap& state_map);
}

#endif	/* HELPERFUNCTIONS_H */

