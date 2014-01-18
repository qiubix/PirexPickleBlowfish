#include "InstantToken.hpp"


InstantToken::InstantToken(Army army, std::string name)
  : Token(army, name) {}


BattleToken::BattleToken(Army army, std::string name)
  : InstantToken(army, name) {}

void BattleToken::action()
{

}


MovementToken::MovementToken(Army army, std::string name)
  : InstantToken(army, name) {}

void MovementToken::action()
{

}


PushToken::PushToken(Army army, std::string name)
  : InstantToken(army, name) {}

void PushToken::action()
{

}


BombToken::BombToken(Army army, std::string name)
  : InstantToken(army, name) {}

void BombToken::action()
{

}


GranadeToken::GranadeToken(Army army, std::string name)
  : InstantToken(army, name) {}

void GranadeToken::action()
{

}


SniperToken::SniperToken(Army army, std::string name)
  : InstantToken(army, name) {}

void SniperToken::action()
{

}
