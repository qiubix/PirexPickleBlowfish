#ifndef QTJSONPARSER_HPP
#define QTJSONPARSER_HPP

#include "JsonParser.hpp"
#include "QtJson.hpp"

class QtJsonParser : public JsonParser
{
public:
  QtJsonParser();
  QtJsonParser(Json* json);
  virtual ~QtJsonParser();

  virtual std::string getStringValue(std::string key);
  virtual int getIntegerValue(std::string key);
  virtual bool getBooleanValue(std::string key);
  virtual void readJsonFromFile(std::string fileName);
  virtual void writeJsonToFile(std::string fileName);

private:
  typedef QtJson JsonType;
  JsonType* json;

};

#endif // QTJSONPARSER_HPP
