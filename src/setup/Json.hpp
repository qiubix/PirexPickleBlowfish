#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <string>
#include <vector>

class Json : public QJsonObject
{
public:
  Json(void);
  Json(QJsonObject object);
  ~Json(void);

  std::string getStringValue(std::string key);
  int getIntegerValue(std::string key);
  bool getBooleanValue(std::string key);
  std::vector<Json> getArray(std::string key);
  Json getObject(std::string key);
  std::vector<std::string> getStringArray(std::string key); //TODO: add test

private:
  QJsonValue takeFromJson(std::string key);

};

#endif // JSON_H
