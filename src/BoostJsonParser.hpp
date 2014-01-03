#ifndef BOOSTJSONPARSER_HPP
#define BOOSTJSONPARSER_HPP

#include "JsonParser.hpp"
#include "BoostJson.hpp"

class BoostJsonParser : public JsonParser
{
public:
  BoostJsonParser();
  virtual ~BoostJsonParser();

  virtual void readJsonFromFile(std::string fileName);
  virtual void writeJsonToFile(std::string fileName);
  virtual std::string getStringValueOfJsonField(std::string field);
  virtual int getIntegerValueOfJsonField(std::string field);

private:
  BoostJson* json;
};

#endif // BOOSTJSONPARSER_HPP
