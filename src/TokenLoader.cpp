#include "TokenLoader.hpp"

#include <cstdlib> //NULL

#include "JsonParser.hpp"

TokenLoader * TokenLoader::instance = NULL;

TokenLoader * TokenLoader::getInstance()
{
  if(instance == NULL) {
    instance = new TokenLoader();
  }
  return instance;
}

TokenLoader::TokenLoader() {
}

Army TokenLoader::getArmy(std::string armyFromJson) {
  static std::map<std::string, Army> armiesDictionary;
  armiesDictionary.insert(std::make_pair<std::string, Army>("Moloch", MOLOCH));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Borgo", BORGO));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Outpost", OUTPOST));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Hegemony", HEGEMONY));

  return armiesDictionary[armyFromJson];
}
