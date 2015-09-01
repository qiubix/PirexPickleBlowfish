#include "StringToEnumTranslator.hpp"

StringToEnumTranslator * StringToEnumTranslator::instance = nullptr;

StringToEnumTranslator * StringToEnumTranslator::getInstance()
{
  if(instance == nullptr) {
    instance = new StringToEnumTranslator();
  }
  return instance;
}

StringToEnumTranslator::StringToEnumTranslator() {
  armiesDictionary.insert(std::make_pair("Moloch", Army::MOLOCH));
  armiesDictionary.insert(std::make_pair("Borgo", Army::BORGO));
  armiesDictionary.insert(std::make_pair("Outpost", Army::OUTPOST));
  armiesDictionary.insert(std::make_pair("Hegemony", Army::HEGEMONY));

  attributesDictionary.insert(std::make_pair("initiative", INITIATIVE));
  attributesDictionary.insert(std::make_pair("toughness", TOUGHNESS));
  attributesDictionary.insert(std::make_pair("melee", MELEE));
  attributesDictionary.insert(std::make_pair("ranged", RANGED));
  attributesDictionary.insert(std::make_pair("shield", SHIELD));
  attributesDictionary.insert(std::make_pair("net", NET));
  attributesDictionary.insert(std::make_pair("medic", MEDIC));
  attributesDictionary.insert(std::make_pair("mother", MOTHER));
  attributesDictionary.insert(std::make_pair("mobility", MOBILITY));
  attributesDictionary.insert(std::make_pair("quartermaster", QUARTERMASTER));

  sidesDictionary.insert(std::make_pair("north", Side::NORTH));
  sidesDictionary.insert(std::make_pair("northEast", Side::NORTH_EAST));
  sidesDictionary.insert(std::make_pair("southEast", Side::SOUTH_EAST));
  sidesDictionary.insert(std::make_pair("south", Side::SOUTH));
  sidesDictionary.insert(std::make_pair("southWest", Side::SOUTH_WEST));
  sidesDictionary.insert(std::make_pair("northWest", Side::NORTH_WEST));

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
