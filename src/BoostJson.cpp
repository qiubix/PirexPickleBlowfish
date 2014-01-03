#include "BoostJson.hpp"

BoostJson::BoostJson() : Json(), ptree()  {
}

BoostJson::~BoostJson() {
}

template<typename T> void BoostJson::addKey(std::string name, T value) {
//  TODO: throw exception when not supported type
}

template<> void BoostJson::addKey<bool>(std::string name, bool value) {
//  this -> put<bool>(name, value);
}

template<> void BoostJson::addKey<int>(std::string name, int value) {
//  this -> put<int>(name, value);
}

template<> void BoostJson::addKey<std::string>(std::string name, std::string value) {
//  this -> put<std::string>(name, value);
}
