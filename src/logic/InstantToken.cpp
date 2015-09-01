#include "InstantToken.hpp"

InstantToken::InstantToken(Army army, std::string name, Controller* controller)
  : Token(army, name) {
  this -> controller = controller;
}


BattleToken::BattleToken(Army army, Controller* controller)
  : InstantToken(army, "Battle", controller) {
}

void BattleToken::action() {
  controller -> setGameState(BATTLE);
  controller->startBattle();
}


MovementToken::MovementToken(Army army, Controller* controller)
  : InstantToken(army, "Movement", controller) {
}

void MovementToken::action() {
  controller -> move(tokenToMove, destination);
}

void MovementToken::setTokenToMove(BoardToken* tokenToMove) {
  this -> tokenToMove = tokenToMove;
}

void MovementToken::setDestination(Field* destination) {
  this -> destination = destination;
}


PushToken::PushToken(Army army, Controller* controller)
  : InstantToken(army, "Push", controller) {
}

void PushToken::action() {
  controller -> move(pushee, destination);
}

void PushToken::setPushingToken(BoardToken* token) {
  pusher = token;
}

void PushToken::setPushedToken(BoardToken* token) {
  pushee = token;
}

void PushToken::setDestination(Field* destination) {
  this -> destination = destination;
}


BombToken::BombToken(Army army, Controller* controller)
  : InstantToken(army, "Bomb", controller) {
}

void BombToken::action() {
  controller -> bombStrikeField(epicentrum);
}

void BombToken::setEpicentrum(Field* epicentrum) {
  this -> epicentrum = epicentrum;
}


GrenadeToken::GrenadeToken(Army army, Controller* controller)
  : InstantToken(army, "Granade", controller) {
}

void GrenadeToken::action() {
  controller -> destroy(toDestroy);
}

void GrenadeToken::setTokenToDestroy(BoardToken* toDestroy) {
  this -> toDestroy = toDestroy;
}


SniperToken::SniperToken(Army army, Controller* controller)
  : InstantToken(army, "Sniper", controller) {
}

void SniperToken::action() {
  controller -> strikeToken(toStrike, 1);
}

void SniperToken::setTokenToStrike(BoardToken* toStrike) {
  this -> toStrike = toStrike;
}
