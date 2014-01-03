#include "BoostJson.hpp"

BoostJson::BoostJson() : Json(), ptree()  {
}

BoostJson::~BoostJson() {
}

std::string BoostJson::getStringValue(std::string key) {
  return this -> get<std::string>(key);
}

int BoostJson::getIntegerValue(std::string key) {
  return this -> get<int>(key);
}

bool BoostJson::getBooleanValue(std::string key) {
  return this -> get<bool>(key);
}

void BoostJson::addStringValue(std::string key, std::string value) {
  this -> put<std::string>(key, value);
}

void BoostJson::addIntegerValue(std::string key, int value) {
  this -> put<int>(key, value);
}

void BoostJson::addBooleanValue(std::string key, bool value) {
  this -> put<bool>(key, value);
}
