#ifndef UNITTOKEN_HPP
#define UNITTOKEN_HPP

#include <map>

#include "BoardToken.hpp"

class UnitToken : public BoardToken
{
public:
  UnitToken(Army army, std::string name, Attributes* attributes = nullptr);
  virtual ~UnitToken();

  //getters
  Attributes* getEdgeAttributes(const Side& edge);

  //TODO: make private
  void setEdgeAttributes(const Side& edge, Attributes* attributes);

private:
  std::map<Side, Attributes*> edges;
};

#endif //UNITTOKEN_HPP
