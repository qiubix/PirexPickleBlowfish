#ifndef TOKEN_LOADER_HPP
#define TOKEN_LOADER_HPP

#include <map>
#include <string>

#include <gtest/gtest.h>

#include <Json.hpp>

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

  void loadArmies(std::vector<std::string> armyJsonFiles);

protected:
  TokenLoader();

private:
  static TokenLoader * instance;

  void loadArmy(std::string armyFile);
  Army getArmy(std::string armyFromJson);
  void loadHeadquarters(Army army, Json headquarters);
  void loadInstantTokens(Army army, std::vector<Json> instantTokens);
  void loadInstantToken(Army army, Json instantToken);
  void loadModuleTokens(Army army, std::vector<Json> moduleTokens);
  void loadModuleToken(Army army, Json moduleToken);
  void loadUnitTokens(Army army, std::vector<Json> unitTokens);
  void loadUnitToken(Army army, Json unitToken);

  //tests for private methods:
  FRIEND_TEST(TokenLoaderTest, shouldReturnArmyFromJson);

};

#endif // TOKEN_LOADER_HPP
