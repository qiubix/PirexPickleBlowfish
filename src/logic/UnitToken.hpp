#ifndef UNITTOKEN_HPP
#define UNITTOKEN_HPP

#include "BoardToken.hpp"

class UnitToken : public BoardToken
{
public:
  UnitToken(Army army, std::string name, Attributes* attributes, Attributes** edgeAttributes);
  ~UnitToken() {}

  //getters
  Attributes* getEdgeAttributes(Side edge);

private:
  //TODO: two derefferentions - messy, wrap it into class with overloaded [] operator
  Attributes** edges;
};

#endif //UNITTOKEN_HPP
