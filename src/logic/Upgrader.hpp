#ifndef UPGRADER_HPP
#define UPGRADER_HPP

#include "Module.hpp"

class Upgrader : public Module
{
public:
  Upgrader(Module* module);
  ~Upgrader() {}

  virtual void addBoardToken(BoardToken *token, Side edge);
  virtual void removeBoardToken(BoardToken *token, Side edge);

protected:
  virtual void upgrade(BoardToken *token);
  virtual void downgrade(BoardToken *token);

private:
  Module* module;
};

#endif //UPGRADER_HPP
