#ifndef RATECONSTANTBASE_H_
#define RATECONSTANTBASE_H_

#include <string>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Common/StateOfTheWorld.h>

namespace ModFossa {
    class StateOfTheWorld;

/** Abstract base class for RateConstants. 
 *
 */

class RateConstantBase {
public:
    typedef ModFossa::shared_ptr<RateConstantBase>::type SharedPointer;
    RateConstantBase();
    virtual ~RateConstantBase();
    virtual double getRate(
            const StateOfTheWorld::SharedPointer state_of_the_world) const = 0;
    virtual std::string getName() const = 0;
};
}
#endif
