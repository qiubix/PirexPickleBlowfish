#ifndef UPGRADE_HPP
#define UPGRADE_HPP

#include "Module.hpp"

class Upgrade : public Module
{
public:
  Upgrade(Module* module);
  ~Upgrade() {}

  virtual void upgrade(BoardToken *token);
  virtual void downgrade(BoardToken *token);
  virtual void addBoardToken(BoardToken *token);
  virtual void removeBoardToken(BoardToken *token);
private:
  Module* module;
};

#endif //UPGRADE_HPP
