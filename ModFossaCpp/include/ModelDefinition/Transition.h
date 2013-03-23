/* 
 * File:   Transition.h
 * Author: gareth
 *
 * Created on March 11, 2013, 7:16 PM
 */

#ifndef TRANSITION_H
#define	TRANSITION_H

#include <ModelDefinition/RateConstantBase.h>
#include <Common/SharedPtr.h>


namespace ModelDefinition {

    class Transition {
    public:
        typedef ModFossa::shared_ptr<Transition>::type SharedPointer;

        Transition(RateConstantBase::SharedPointer rate_constant,
                bool sign) :
        rate_constant(rate_constant),
        sign(sign) {

        }

        const RateConstantBase::SharedPointer rate_constant;
        const bool sign;
    };
}


#endif	/* TRANSITION_H */

