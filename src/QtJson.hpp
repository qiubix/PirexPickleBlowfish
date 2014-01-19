#ifndef QTJSON_H
#define QTJSON_H

#include <Json.hpp>
#include <QJsonObject>

class QtJson: public Json, public QJsonObject
{
public:
  QtJson();
  virtual ~QtJson();

  virtual std::string getStringValue(std::string key);
  virtual int getIntegerValue(std::string key);
  virtual bool getBooleanValue(std::string key);

  virtual void addStringValue(std::string key, std::string value);
  virtual void addIntegerValue(std::string key, int value);
  virtual void addBooleanValue(std::string key, bool value);
};

#endif // QTJSON_H
