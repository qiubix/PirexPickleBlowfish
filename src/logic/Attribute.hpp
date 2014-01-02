#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <string>

class Attribute
{
public:
  Attribute(std::string name, int baseValue);
  std::string getName(void);
  int getValue(void);
  void upgradeAttribute(void);
  void downgradeAttribute(void);
private:
  std::string name;
  int baseValue;
  int currentValue;
};

#endif //ATTRIBUTE_HPP
