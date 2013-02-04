#ifndef _RATECONSTANTFACTORY_H
#define _RATECONSTANTFACTORY_H

#include <memory>

#include "RateConstantType.h"

class RateConstantBase;

class RateConstantFactory
{
public:
	RateConstantFactory();
	~RateConstantFactory();
	std::unique_ptr<RateConstantBase> AddRateConstant(
		RateConstantType type);
};
#endif
