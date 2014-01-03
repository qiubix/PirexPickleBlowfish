#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>

class JsonParser{
public:
  JsonParser(void) {}
  virtual ~JsonParser(void) {}

  virtual std::string getStringValue(std::string key) = 0;
  virtual int getIntegerValue(std::string key) = 0;
  virtual bool getBooleanValue(std::string key) = 0;
  virtual void readJsonFromFile(std::string fileName) = 0;
  virtual void writeJsonToFile(std::string fileName) = 0;
};

#endif // JSONPARSER_H
