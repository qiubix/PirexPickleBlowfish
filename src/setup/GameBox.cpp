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
  std::map<Army, std::vector<Token *> >::iterator it;
  it = armies.find(armyName);
  if(it == armies.end())
    throw NoSuchArmyInBoxException();
  else
    return it -> second;
}

void GameBox::addArmy(Army armyName, std::vector<Token *> army) {
  armies.insert(std::make_pair<Army, std::vector<Token *> >(armyName, army));
}
