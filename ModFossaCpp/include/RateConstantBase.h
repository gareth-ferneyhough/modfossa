#ifndef _RATECONSTANTBASE_H
#define _RATECONSTANTBASE_H

#include <string>

using std::string;

class StateOfTheWorld;

/** Abstract base class for RateConstants. 
 *
 */
	
class RateConstantBase
{
public:
	RateConstantBase();
	virtual ~RateConstantBase();
	virtual double GetRate(StateOfTheWorld* stateOfTheWorld) = 0; 
        virtual string GetName() const = 0;
        virtual void SetName(string name) = 0;
};
#endif
