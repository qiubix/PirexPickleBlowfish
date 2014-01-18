#ifndef INSTANTTOKEN_HPP
#define INSTANTTOKEN_HPP

#include "Token.hpp"

class InstantToken : public Token
{
public:
  InstantToken(Army army, std::string name);
  virtual ~InstantToken(void) {}

  virtual void action(void) = 0;
};

class BattleToken : public InstantToken
{
public:
  BattleToken(Army army, std::string name = "Battle");
  ~BattleToken(void) {}

  void action(void);
};

class MovementToken : public InstantToken
{
public:
  MovementToken(Army army, std::string name = "Movement");
  ~MovementToken() {}

  void action(void);
};

class PushToken : public InstantToken
{
public:
  PushToken(Army army, std::string name = "Push");
  ~PushToken() {}

  void action(void);
};

class BombToken : public InstantToken
{
public:
  BombToken(Army army, std::string name = "Bomb");
  ~BombToken() {}

  void action(void);
};

class GranadeToken : public InstantToken
{
public:
  GranadeToken(Army army, std::string name = "Granade");
  ~GranadeToken() {}

  void action(void);
};

class SniperToken : public InstantToken
{
public:
  SniperToken(Army army, std::string name = "Sniper");
  ~SniperToken() {}

  void action(void);
};

#endif //INSTANTTOKEN_HPP
