/*
 * Transition.h
 *
 *  Created on: Jul 10, 2012
 *      Author: gareth
 */

typedef std::string StateName;

class Transition {
public:
    StateName source;
    double rate;
};
