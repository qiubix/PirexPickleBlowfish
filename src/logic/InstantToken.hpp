#ifndef INSTANTTOKEN_HPP
#define INSTANTTOKEN_HPP

#include "Token.hpp"
#include "Controller.hpp"
#include "BoardToken.hpp"

class InstantToken : public Token
{
public:
  InstantToken(Army army, std::string name, Controller* controller);
  virtual ~InstantToken(void) {}

  virtual void action(void) = 0;
protected:
  Controller* controller;

  //tests for private methods:
  FRIEND_TEST(TokenLoaderTest, shouldCreateBattleToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateMovementToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreatePushToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateBombToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateGrenadeToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateSniperToken);

};

class BattleToken : public InstantToken
{
public:
  BattleToken(Army army, Controller* controller);
  ~BattleToken(void) {}

  void action(void);
};

class MovementToken : public InstantToken
{
public:
  MovementToken(Army army, Controller* controller);
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
  PushToken(Army army, Controller* controller);
  ~PushToken() {}

  void action(void);

  void setPushingToken(BoardToken* token);
  void setPushedToken(BoardToken* token);
  void setDestination(Field* destination);
private:
  BoardToken* pusher;
  BoardToken* pushee;
  Field* destination;
};

class BombToken : public InstantToken
{
public:
  BombToken(Army army, Controller* controller);
  ~BombToken() {}

  void action(void);
  void setEpicentrum(Field* epicentrum);

private:
  Field* epicentrum;
};

class GrenadeToken : public InstantToken
{
public:
  GrenadeToken(Army army, Controller* controller);
  ~GrenadeToken() {}

  void action(void);
  void setTokenToDestroy(BoardToken* toDestroy);

private:
  BoardToken* toDestroy;
};

class SniperToken : public InstantToken
{
public:
  SniperToken(Army army, Controller* controller);
  ~SniperToken() {}

  void action(void);
  void setTokenToStrike(BoardToken* toStrike);

private:
  BoardToken* toStrike;
};

#endif //INSTANTTOKEN_HPP
