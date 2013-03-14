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
        typedef shared_ptr<Transition> SharedPointer;

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

