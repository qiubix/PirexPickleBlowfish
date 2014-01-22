#ifndef TOKEN_LOADER_HPP
#define TOKEN_LOADER_HPP

#include <map>
#include <string>

#include <gtest/gtest.h>

#include "Json.hpp"
#include "StringToEnumTranslator.hpp"

#include "logic/ModuleToken.hpp"
#include "logic/UnitToken.hpp"

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

  void loadHeadquarters(Army army, Json headquarters);

  void loadInstantTokens(Army army, std::vector<Json> instantTokens);
  void loadInstantToken(Army army, Json instantToken);

  void loadModuleTokens(Army army, std::vector<Json> moduleTokens);
  void loadModuleToken(Army army, Json moduleToken);
  Attributes* loadModuleAtrributes(std::vector<Json> attributes);
  Attribute* loadModuleAttribute(Json attribute);
  std::vector<Side> loadModuleActiveEdges(std::vector<std::string> edges);
  Module* decorateModuleWithUpgrades(ModuleToken* moduleToken, std::vector<Json> upgrades);

  void loadUnitTokens(Army army, std::vector<Json> unitTokens);
  void loadUnitToken(Army army, Json unitToken);

  //tests for private methods:
  FRIEND_TEST(TokenLoaderTest, shouldLoadModuleAttributes);
  FRIEND_TEST(TokenLoaderTest, shouldLoadModuleActiveEdges);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithUpgrades);

};

#endif // TOKEN_LOADER_HPP
