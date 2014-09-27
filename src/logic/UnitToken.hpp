#ifndef UNITTOKEN_HPP
#define UNITTOKEN_HPP

#include "BoardToken.hpp"

class UnitToken : public BoardToken
{
public:
  UnitToken(Army army, std::string name, Attributes* attributes = nullptr);
  virtual ~UnitToken();

  //getters
  Attributes* getEdgeAttributes(Side edge);

  //TODO: make private
  void setEdgeAttributes(Side edge, Attributes* attributes);

private:
  //REVIEW: avoid **
  Attributes** edges;
};

#endif //UNITTOKEN_HPP
