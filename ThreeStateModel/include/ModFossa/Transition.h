/*
 * Transition.h
 *
 *  Created on: Jul 10, 2012
 *      Author: gareth
 */

#include <string>
#include <ModFossa/RateConstant.h>

typedef std::string StateName;

class Transition {
public:
    Transition() :
            rate(NULL) {
    }

    StateName source;
    RateConstant* rate;
};
