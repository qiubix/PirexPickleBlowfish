#include "BoostJsonParser.hpp"

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::read_json;

BoostJsonParser::BoostJsonParser() : JsonParser() {
  json = new JsonType();
}

BoostJsonParser::BoostJsonParser(Json* json) : JsonParser() {
  this -> json = dynamic_cast<BoostJson*>(json);
}

BoostJsonParser::~BoostJsonParser() {
  delete json;
}

std::string BoostJsonParser::getStringValue(std::string key) {
  return json -> getStringValue(key);
}

int BoostJsonParser::getIntegerValue(std::string key) {
  return json -> getIntegerValue(key);
}

bool BoostJsonParser::getBooleanValue(std::string key) {
  return json -> getBooleanValue(key);
}

void BoostJsonParser::readJsonFromFile(std::string fileName) {
  read_json(fileName, *dynamic_cast<ptree*>(json));
}

void BoostJsonParser::writeJsonToFile(std::string fileName) {

}
