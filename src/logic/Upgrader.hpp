#ifndef UPGRADER_HPP
#define UPGRADER_HPP

#include "Module.hpp"

class Upgrader : public Module
{
public:
  Upgrader(Module* module, bool affectsEnemies);
  virtual ~Upgrader() {}

  virtual void addBoardToken(BoardToken* token);
  virtual void removeBoardToken(BoardToken* token);
  bool isAffectingEnemies(void);

protected:
  virtual void upgrade(BoardToken *token);
  virtual void downgrade(BoardToken *token);

  bool affectsEnemies;

private:
  Module* module;

};

#endif //UPGRADER_HPP
