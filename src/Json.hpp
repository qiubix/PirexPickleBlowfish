#ifndef JSON_HPP
#define JSON_HPP

#include <string>

class Json
{
public:
  Json(void) {}
  virtual ~Json(void) {}

  virtual std::string getStringValue(std::string key) = 0;
  virtual int getIntegerValue(std::string key) = 0;
  virtual bool getBooleanValue(std::string key) = 0;

  virtual void addStringValue(std::string key, std::string value) = 0;
  virtual void addIntegerValue(std::string key, int value) = 0;
  virtual void addBooleanValue(std::string key, bool value) = 0;

};

#endif // JSON_HPP
