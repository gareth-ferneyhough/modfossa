#ifndef _CONSTANTRATECONSTANT_H
#define _CONSTANTRATECONSTANT_H

#include "RateConstantBase.h"
#include <string>

using std::string;

class ConstantRateConstant
{
public:
  ConstantRateConstant(string name, double k);
  virual ~ConstantRateConstant();
  virtual double GetRate(StateOfTheWorld* stateOfTheWorld);
  
 private:
  const string name;
  const double k;
};
#endif
