#ifndef UNIT_HPP
#define UNIT_HPP

#include "BoardToken.hpp"

class Unit : public BoardToken
{
public:
  Unit(Army army, std::string name, Attributes* attributes, Attributes** sideAttributes);
  ~Unit() {}

  //getters
  Attributes* getSideAttributes(Side side);

private:
  Attributes** side;
};

#endif //UNIT_HPP
