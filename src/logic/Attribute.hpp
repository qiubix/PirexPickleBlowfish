#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <string>

class Attribute
{
public:
  Attribute(std::string name, int baseValue);

  void upgradeBy(int amount = 1);
  void downgradeBy(int amount = 1);
  void upgradeTo(int newValue);
  void downgradeTo(int newValue);
  void resetValue();

  //getters
  std::string getName();
  int getValue();

private:
  std::string name;
  int baseValue;
  int currentValue;
};

#endif //ATTRIBUTE_HPP
