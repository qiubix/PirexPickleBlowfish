#ifndef INSTANTTOKEN_HPP
#define INSTANTTOKEN_HPP

#include "Token.hpp"
#include "Controller.hpp"
#include "BoardToken.hpp"

class InstantToken : public Token
{
public:
  InstantToken(Army army, Controller* controller, std::string name);
  virtual ~InstantToken(void) {}

  virtual void action(void) = 0;
protected:
  Controller* controller;
};

class BattleToken : public InstantToken
{
public:
  BattleToken(Army army, Controller* controller, std::string name = "Battle");
  ~BattleToken(void) {}

  void action(void);
};

class MovementToken : public InstantToken
{
public:
  MovementToken(Army army, Controller* controller, std::string name = "Movement");
  ~MovementToken() {}

  void action(void);
  void setTokenToMove(BoardToken* tokenToMove);
  void setDestination(Field* destination);
private:
  BoardToken* tokenToMove;
  Field* destination;
};

class PushToken : public InstantToken
{
public:
  PushToken(Army army, Controller* controller, std::string name = "Push");
  ~PushToken() {}

  void action(void);

  void setPushingToken(BoardToken* token);
  void setPushedToken(BoardToken* token);
private:
  BoardToken* pusher;
  BoardToken* pushee;
};

class BombToken : public InstantToken
{
public:
  BombToken(Army army, Controller* controller, std::string name = "Bomb");
  ~BombToken() {}

  void action(void);
  void setEpicentrum(Field* epicentrum);

private:
  Field* epicentrum;
};

class GranadeToken : public InstantToken
{
public:
  GranadeToken(Army army, Controller* controller, std::string name = "Granade");
  ~GranadeToken() {}

  void action(void);
  void setTokenToDestroy(BoardToken* toDestroy);

private:
  BoardToken* toDestroy;
};

class SniperToken : public InstantToken
{
public:
  SniperToken(Army army, Controller* controller, std::string name = "Sniper");
  ~SniperToken() {}

  void action(void);
};

#endif //INSTANTTOKEN_HPP
