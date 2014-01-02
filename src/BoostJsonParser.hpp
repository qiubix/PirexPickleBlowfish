#ifndef BOOSTJSONPARSER_HPP
#define BOOSTJSONPARSER_HPP

#include "JsonParser.hpp"

#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

class BoostJsonParser : public JsonParser
{
public:
  BoostJsonParser();
  ~BoostJsonParser();

  void readJsonFromFile(std::string fileName);
  void writeJsonToFile(std::string fileName);
  std::string getStringValueOfJsonField(std::string field);
  int getIntegerValueOfJsonField(std::string field);

private:
  typedef boost::property_tree::ptree Json;
  Json json;
};

#endif // BOOSTJSONPARSER_HPP
