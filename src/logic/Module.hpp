#ifndef MODULE_HPP
#define MODULE_HPP

#include "BoardToken.hpp"

class Module : public BoardToken
{
public:
  Module(Army army, std::string name, Attributes* attributes);
  ~Module() {}

  virtual void addBoardToken(BoardToken* token, Side edge) = 0;
  virtual void removeBoardToken(BoardToken* token, Side edge) = 0;
};

#endif //MODULE_HPP
