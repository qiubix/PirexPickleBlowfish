#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <string>

class Attribute
{
public:
  Attribute(std::string name, int baseValue);

  void upgrade(int amount = 1);
  void downgrade(int amount = 1);

  //getters
  std::string getName(void);
  int getValue(void);

private:
  std::string name;
  int baseValue;
  int currentValue;
};

#endif //ATTRIBUTE_HPP
