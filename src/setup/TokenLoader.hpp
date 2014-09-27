#ifndef TOKEN_LOADER_HPP
#define TOKEN_LOADER_HPP

#include <map>
#include <string>

#include <gtest/gtest.h>

#include "Json.hpp"
#include "StringToEnumTranslator.hpp"

#include "../logic/ModuleToken.hpp"
#include "../logic/UnitToken.hpp"
#include "../logic/InstantToken.hpp"
#include "../logic/HeadquartersToken.hpp"

#include "../logic/Upgrader.hpp"

#include "../logic/Controller.hpp"

class TokenLoader
{
public:
  static TokenLoader * getInstance();

  void loadArmies(std::vector<std::string> armyJsonFiles, Controller* controller);

protected:
  TokenLoader();

private:
  static TokenLoader * instance;

  void loadArmy(std::string armyFile, Controller* controller);

  void loadHeadquarters(Army army, Json headquartersParameters);
  Module* createHeadquarters(Army army, Json& upgradeParameters);

  void loadInstantTokens(Army army, std::vector<Json> instantTokens, Controller* controller);
  void loadInstantToken(Army army, Json instantToken, Controller* controller);
  InstantToken* createInstantToken(Army army, std::string name, Controller* controller);

  void loadModuleTokens(Army army, std::vector<Json> moduleTokens);
  void loadModuleToken(Army army, Json moduleToken);
  Attributes* loadModuleAtrributes(std::vector<Json> attributes);
  Attribute* loadModuleAttribute(Json attribute);
  std::vector<Side> loadModuleActiveEdges(std::vector<std::string> edges);
  Module* decorateModuleWithUpgrades(ModuleToken* moduleToken, std::vector<Json> upgrades);

  void loadUnitTokens(Army army, std::vector<Json> unitTokens);
  void loadUnitToken(Army army, Json unitToken);
  Attributes* loadUnitAttributes(Json unitTokenParameters);
  void loadInitiative(std::vector<int>, Attributes* attributes);
  void loadMove(bool haveMoveAbility, Attributes* attributes);
  void loadToughness(int additionalToughness, Attributes* attributes);
  void loadUnitSideAttributes(UnitToken* token, Json unitTokenParameters);
  void loadMelee(UnitToken* token, Json& meleeParameters);
  void loadRanged(UnitToken* token, Json& rangedParameters);
  void loadShield(UnitToken* token, std::vector<std::string> armorParameters);
  void loadNet(UnitToken* token, std::vector<std::string> netParameters);

  //tests for private methods:
  FRIEND_TEST(TokenLoaderTest, shouldLoadModuleAttributes);
  FRIEND_TEST(TokenLoaderTest, shouldLoadModuleActiveEdges);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithTwoChangeAttributeUpgrades);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithOneChangeAttributeOfEnemyUpgrade);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithChangeArmyUpgrade);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithTwoAddAttributeUpgrades);
  FRIEND_TEST(TokenLoaderTest, shouldDecorateModuleWithOneAddAttributeAndOneChangeAttributeUpgrades);

  FRIEND_TEST(TokenLoaderTest, shouldAddInitiativeLoadedFromJsonToAttributes);
  FRIEND_TEST(TokenLoaderTest, shouldAddMobilityFromJsonToAttributes);
  FRIEND_TEST(TokenLoaderTest, shouldAddToughnessFromJsonToAttributes);
  FRIEND_TEST(TokenLoaderTest, shouldAddMeleeAttributesToToken);
  FRIEND_TEST(TokenLoaderTest, shouldAddRangedAttributesToToken);
  FRIEND_TEST(TokenLoaderTest, shouldAddShieldAttributesToToken);
  FRIEND_TEST(TokenLoaderTest, shouldAddNetAttributesToToken);

  FRIEND_TEST(TokenLoaderTest, shouldCreateBattleToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateMovementToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreatePushToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateBombToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateGrenadeToken);
  FRIEND_TEST(TokenLoaderTest, shouldCreateSniperToken);

  FRIEND_TEST(TokenLoaderTest, shouldCreateHeadquartersTokenUpgradingAttribute);
  FRIEND_TEST(TokenLoaderTest, shouldCreateHeadquartersTokenAddingAttribute);

};

#endif // TOKEN_LOADER_HPP
