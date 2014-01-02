#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>

class JsonParser{
public:
  JsonParser(void);
  virtual ~JsonParser(void) = 0;

  virtual void readJsonFromFile(std::string fileName) = 0;
  virtual void writeJsonToFile(std::string fileName) = 0;
  virtual std::string getStringValueOfJsonField(std::string field) = 0;
  virtual int getIntegerValueOfJsonField(std::string field) = 0;

};

#endif // JSONPARSER_H
