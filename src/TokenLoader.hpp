#ifndef TOKEN_LOADER_HPP
#define TOKEN_LOADER_HPP

#include <map>
#include <string>

#include <gtest/gtest.h>

//FIXME: use enum from Token then
enum Army {
  MOLOCH,
  BORGO,
  OUTPOST,
  HEGEMONY
};

class TokenLoader
{
public:
  static TokenLoader * getInstance();

  void loadArmies(std::string armies);

protected:
  TokenLoader();

private:
  static TokenLoader * instance;

  Army getArmy(std::string armyFromJson);

  //tests for private methods:
  FRIEND_TEST(TokenLoaderTest, shouldReturnArmyFromJson);

};

#endif // TOKEN_LOADER_HPP
