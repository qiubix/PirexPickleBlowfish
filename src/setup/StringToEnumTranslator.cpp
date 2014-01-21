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

  sidesDictionary.insert(std::make_pair<std::string, Side>("north", NORTH));
  sidesDictionary.insert(std::make_pair<std::string, Side>("northEast", NORTH_EAST));
  sidesDictionary.insert(std::make_pair<std::string, Side>("southEast", SOUTH_EAST));
  sidesDictionary.insert(std::make_pair<std::string, Side>("south", SOUTH));
  sidesDictionary.insert(std::make_pair<std::string, Side>("southWest", SOUTH_WEST));
  sidesDictionary.insert(std::make_pair<std::string, Side>("northWest", NORTH_WEST));

}

Army StringToEnumTranslator::getArmy(std::string army) {
  return armiesDictionary[army];
}

AttributeName StringToEnumTranslator::getAttributeName(std::string attribute) {
  return attributesDictionary[attribute];
}

Side StringToEnumTranslator::getSide(std::string side) {
  return sidesDictionary[side];
}
