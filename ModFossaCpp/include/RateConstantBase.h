#ifndef RATECONSTANTBASE_H_
#define RATECONSTANTBASE_H_

#include <string>

using std::string;

class StateOfTheWorld;

/** Abstract base class for RateConstants. 
 *
 */

class RateConstantBase {
public:
    RateConstantBase();
    virtual ~RateConstantBase();
    virtual double getRate(StateOfTheWorld* stateOfTheWorld) = 0;
    virtual string getName() const = 0;
    virtual void setName(string name) = 0;
};
#endif
