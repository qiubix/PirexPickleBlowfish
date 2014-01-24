#ifndef GAME_BOX_H
#define GAME_BOX_H

#include <map>
#include <vector>

#include "logic/Army.hpp"
#include "logic/Token.hpp"

#include <gtest/gtest.h>

#include "GameBoxExceptions.hpp"

class GameBox
{
public:
  static GameBox * getInstance();

  int getArmiesCount(void);
  bool isEmpty(void);
  std::vector<Token *> getArmy(Army armyName);

protected:
  GameBox();
  void addArmy(Army armyName, std::vector<Token *> army);

private:
  static GameBox * instance;

  std::map<Army, std::vector<Token *> > armies;

  //tests for private methods (to access protected constructor)
  FRIEND_TEST(GameBoxTest, shouldReturnArmiesCountInTheBox);
  FRIEND_TEST(GameBoxTest, shouldReturnIfThereIsNoArmiesInTheBox);
  FRIEND_TEST(GameBoxTest, shouldGetArmyFromTheBox);
  FRIEND_TEST(GameBoxTest, shouldAddArmyToTheBox);

};

#endif // GAME_BOX_H
