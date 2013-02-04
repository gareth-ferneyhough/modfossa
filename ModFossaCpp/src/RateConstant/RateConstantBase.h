#ifndef _RATECONSTANTBASE_H
#define _RATECONSTANTBASE_H

#include <string>

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
};
#endif
