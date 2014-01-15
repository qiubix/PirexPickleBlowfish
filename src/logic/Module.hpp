#ifndef MODULE_HPP
#define MODULE_HPP

#include "BoardToken.hpp"

class Module : public BoardToken
{
public:
  Module();
  Module(Army army, std::string name, Attributes* attributes);
  ~Module() {}

  virtual void addBoardToken(BoardToken* token) = 0;
  virtual void removeBoardToken(BoardToken* token) = 0;
};

#endif //MODULE_HPP
