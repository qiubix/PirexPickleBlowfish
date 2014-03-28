#include "GameBox.hpp"

#include <cstdlib>

#include <exception>

GameBox * GameBox::instance = NULL;

GameBox * GameBox::getInstance()
{
  if(instance == NULL) {
    instance = new GameBox();
  }
  return instance;
}

GameBox::GameBox() {
}

int GameBox::getArmiesCount(void) {
  return armies.size();
}

bool GameBox::isEmpty(void) {
  return getArmiesCount() == 0;
}

std::vector<Token *> GameBox::getArmy(Army armyName) {
  if(containsArmy(armyName))
    return armies[armyName];
  else
    throw NoSuchArmyInBoxException();
}

void GameBox::addArmy(Army armyName, std::vector<Token *> army) {
  if(!containsArmy(armyName))
    armies.insert(std::make_pair(armyName, army));
//    armies.insert(std::make_pair<Army, std::vector<Token *> >(armyName, army));
  //TODO: else: throw ThereIsAlreadySuchArmyInTheBoxException
}

void  GameBox::addTokenToArmy(Army armyName, Token* token) {
  if(containsArmy(armyName))
    armies[armyName].push_back(token);
  else
    throw NoSuchArmyInBoxException();
}

bool GameBox::containsArmy(Army armyName) {
  std::map<Army, std::vector<Token *> >::iterator it;
  it = armies.find(armyName);
  if(it == armies.end())
    return false;
  return true;
}

void GameBox::addEmptyArmy(Army armyName) {
  std::vector<Token *> army;
  addArmy(armyName, army);
}
