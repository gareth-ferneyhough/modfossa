/* 
 * File:   Transition.h
 * Author: gareth
 *
 * Created on March 11, 2013, 7:16 PM
 */

#ifndef TRANSITION_H
#define	TRANSITION_H

#include <memory>
#include <ModelDefinition/RateConstantBase.h>

using std::shared_ptr;

namespace ModelDefinition {
    class Transition {
    public:
        typedef shared_ptr<const Transition> SharedPointer;
        RateConstantBase::SharedPointer rate_constant;
        bool sign;
    };
}


#endif	/* TRANSITION_H */

