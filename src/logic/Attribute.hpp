#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <string>

class Attribute
{
  std::string name;
  int baseValue;
  int upgradedValue;
public:
  Attribute(std::string name, int baseValue);
  std::string getName();
  int getBaseValue();
  int getUpgradedValue();
};

#endif //ATTRIBUTE_HPP
