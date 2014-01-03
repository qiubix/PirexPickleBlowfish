#ifndef BOOSTJSONPARSER_HPP
#define BOOSTJSONPARSER_HPP

#include "JsonParser.hpp"
#include "BoostJson.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//typedef boost::property_tree::ptree Json;

class BoostJsonParser : public JsonParser
{
public:
  BoostJsonParser();
  virtual ~BoostJsonParser();

  virtual void readJsonFromFile(std::string fileName);
  virtual void writeJsonToFile(std::string fileName);
  virtual std::string getStringValueOfJsonField(std::string field);
  virtual int getIntegerValueOfJsonField(std::string field);

//private:
//  Json json;
};

#endif // BOOSTJSONPARSER_HPP
