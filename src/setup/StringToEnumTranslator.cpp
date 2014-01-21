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

  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("initiative", INITIATIVE));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("toughness", TOUGHNESS));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("melee", MELEE));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("ranged", RANGED));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("shield", SHIELD));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("net", NET));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("medic", MEDIC));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("mother", MOTHER));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("mobility", MOBILITY));
  attributesDictionary.insert(std::make_pair<std::string, AttributeName>("quartermaster", QUARTERMASTER));

}

Army StringToEnumTranslator::getArmy(std::string army) {
  return armiesDictionary[army];
}

AttributeName StringToEnumTranslator::getAttributeName(std::string attribute) {
  return attributesDictionary[attribute];
}
