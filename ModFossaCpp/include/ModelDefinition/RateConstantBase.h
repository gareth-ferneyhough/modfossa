#ifndef RATECONSTANTBASE_H_
#define RATECONSTANTBASE_H_

#include <string>
#include <memory>
#include <ModelDefinition/StateOfTheWorld.h>

using std::string;
using std::shared_ptr;

namespace ModelDefinition {
    class StateOfTheWorld;

    /** Abstract base class for RateConstants. 
     *
     */

    class RateConstantBase {
    public:
        typedef shared_ptr<RateConstantBase> SharedPointer;
        RateConstantBase();
        virtual ~RateConstantBase();
        virtual double getRate(
                const StateOfTheWorld::SharedPointer state_of_the_world) const = 0;
        virtual string getName() const = 0;
    };
}
#endif
