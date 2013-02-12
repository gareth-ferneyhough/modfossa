#include <ConstantRateConstant.h>

ConstantRateConstant::ConstantRateConstant() :
  RateConstantBase()
{
}

ConstantRateConstant::ConstantRateConstant(string name, double k) :
  RateConstantBase(),
  name(name),
  k(k)
{
}

ConstantRateConstant::~ConstantRateConstant()
{
}

double ConstantRateConstant::GetRate(StateOfTheWorld* stateOfTheWorld)
{
  return k;
}

string ConstantRateConstant::GetName() const
{
  return name;
}

void ConstantRateConstant::SetName(string name)
{
  this-> name = name;
}
