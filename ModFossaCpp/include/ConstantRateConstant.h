#ifndef _CONSTANTRATECONSTANT_H
#define _CONSTANTRATECONSTANT_H

#include <RateConstantBase.h>
#include <string>

using std::string;

class ConstantRateConstant : public RateConstantBase
{
 public:
  ConstantRateConstant();
  ConstantRateConstant(string name, double k);
  virtual ~ConstantRateConstant();
  virtual double GetRate(StateOfTheWorld* stateOfTheWorld);
  string GetName() const;
  void SetName(string name);
 
 private:
  string name;
  double k;
};
#endif
