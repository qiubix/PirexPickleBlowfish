#include "StringToEnumTranslator.hpp"

StringToEnumTranslator * StringToEnumTranslator::instance = NULL;

StringToEnumTranslator * StringToEnumTranslator::getInstance()
{
  if(instance == NULL) {
    instance = new StringToEnumTranslator();
  }
  return instance;
}

StringToEnumTranslator::StringToEnumTranslator() {
  armiesDictionary.insert(std::make_pair<std::string, Army>("Moloch", MOLOCH));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Borgo", BORGO));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Outpost", OUTPOST));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Hegemony", HEGEMONY));
}

Army StringToEnumTranslator::getArmy(std::string army) {
  return armiesDictionary[army];
}
