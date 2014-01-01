#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <string>

class Attribute
//REVIEW: same comment according to sections naming and order as in BoardToken class
{
  std::string name;
  int baseValue;
  int upgradedValue;
public:
  Attribute(std::string name, int baseValue);
  std::string getName();
  //REVIEW: do we ever need base value in other places? i mean if we get value of some attribute we are probably
  // looking for the upgraded value so maybe this getter is redundant (now for sure)
  int getBaseValue();
  //REVIEW: maybe this getter can be named getValue (because of the reason of that i wrote above) so that would better say what it does
  //and base value is only for internal use i guess (we can discuss it)
  int getUpgradedValue();
  //REVIEW: i think that upgrading value should be done not by setting but by adding or substracting a value (from model upgrade)
  void upgradeAttribute(int newValue);
};

#endif //ATTRIBUTE_HPP
