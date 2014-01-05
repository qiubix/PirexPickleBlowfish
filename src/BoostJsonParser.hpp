#ifndef BOOSTJSONPARSER_HPP
#define BOOSTJSONPARSER_HPP

#include "JsonParser.hpp"
#include "BoostJson.hpp"

class BoostJsonParser : public JsonParser
{
public:
  BoostJsonParser();
  BoostJsonParser(Json* json);
  virtual ~BoostJsonParser();

  virtual std::string getStringValue(std::string key);
  virtual int getIntegerValue(std::string key);
  virtual bool getBooleanValue(std::string key);
  virtual void readJsonFromFile(std::string fileName);
  virtual void writeJsonToFile(std::string fileName);

private:
  typedef BoostJson JsonType;
  JsonType* json;

};

#endif // BOOSTJSONPARSER_HPP
