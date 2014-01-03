#include "BoostJsonParser.hpp"

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::read_json;

BoostJsonParser::BoostJsonParser() : JsonParser() {
  json = new BoostJson();
}

BoostJsonParser::~BoostJsonParser() {
  delete json;
}

void BoostJsonParser::readJsonFromFile(std::string fileName) {
//  read_json(fileName, json);
}

void BoostJsonParser::writeJsonToFile(std::string fileName) {

}

std::string BoostJsonParser::getStringValueOfJsonField(std::string field) {
//  return json.get<std::string>(field);
}

int BoostJsonParser::getIntegerValueOfJsonField(std::string field) {
//  return json.get<int>(field);
}
