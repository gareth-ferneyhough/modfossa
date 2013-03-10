#ifndef RATECONSTANTBASE_H_
#define RATECONSTANTBASE_H_

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

namespace ModelDefinition {
    class StateOfTheWorld;

    /** Abstract base class for RateConstants. 
     *
     */

    class RateConstantBase {
    public:
        RateConstantBase();
        virtual ~RateConstantBase();
		virtual double getRate(const shared_ptr<const StateOfTheWorld> state_of_the_world) const = 0;
        virtual string getName() const = 0;
    };
}
#endif
