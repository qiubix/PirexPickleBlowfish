#include "InstantToken.hpp"


InstantToken::InstantToken(Army army, Controller* controller, std::string name)
  : Token(army, name) {
  this->controller = controller;
}


BattleToken::BattleToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void BattleToken::action()
{
  controller->setGameState(BATTLE);
}


MovementToken::MovementToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void MovementToken::action()
{
  Attribute* mobility = new Attribute("mobility", 1);
  tokenToMove->addAttribute(MOBILITY, mobility);
//  controller->activate(tokenToMove);
  controller->move(tokenToMove, destination);
}

void MovementToken::setTokenToMove(BoardToken* tokenToMove)
{
  this->tokenToMove = tokenToMove;
}

void MovementToken::setDestination(Field* destination)
{
  this->destination = destination;
}


PushToken::PushToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void PushToken::action()
{
  controller->move(pushee, destination);
}

void PushToken::setPushingToken(BoardToken* token)
{
  pusher = token;
}

void PushToken::setPushedToken(BoardToken* token)
{
  pushee = token;
}

void PushToken::setDestination(Field* destination)
{
  this->destination = destination;
}


BombToken::BombToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void BombToken::action()
{
  controller->bombStrikeField(epicentrum);
}

void BombToken::setEpicentrum(Field* epicentrum)
{
  this->epicentrum = epicentrum;
}


GranadeToken::GranadeToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void GranadeToken::action()
{
  controller->destroy(toDestroy);
}

void GranadeToken::setTokenToDestroy(BoardToken* toDestroy)
{
  this->toDestroy = toDestroy;
}


SniperToken::SniperToken(Army army, Controller* controller, std::string name)
  : InstantToken(army, controller, name) {}

void SniperToken::action()
{

}
