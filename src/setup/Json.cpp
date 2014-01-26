#include "Json.hpp"

#include <QStringList>
#include <QVector>

Json::Json(void) : QJsonObject() {
}

Json::Json(QJsonObject object) : QJsonObject(object) {
}

Json::~Json(void) {
}

std::string Json::getStringValue(std::string key) {
  return takeFromJson(key).toString().toStdString();
}

int Json::getIntegerValue(std::string key) {
  return static_cast<int>(takeFromJson(key).toDouble());
}

bool Json::getBooleanValue(std::string key) {
  return takeFromJson(key).toBool();
}

std::vector<Json> Json::getArray(std::string key) {
  QJsonArray array = takeFromJson(key).toArray();
  std::vector<Json> vector;
  for(int i = 0; i < array.size(); i++) {
    if(array.at(i).isObject())
      vector.push_back(array.at(i).toObject());
  }
  return vector;
}

Json Json::getObject(std::string key) {
  return Json(takeFromJson(key).toObject());
}

std::vector<std::string> Json::getStringArray(std::string key) {
  QJsonArray array = takeFromJson(key).toArray();
  std::vector<std::string> vector;
  for(int i = 0; i < array.size(); i++) {
    if(array.at(i).isString())
      vector.push_back(array.at(i).toString().toStdString());
  }
  return vector;
}

std::vector<int> Json::getIntegerArray(std::string key) {
  QJsonArray array = takeFromJson(key).toArray();
  std::vector<int> vector;
  for(int i = 0; i < array.size(); i++) {
    if(array.at(i).isDouble())
      vector.push_back(static_cast<int>(array.at(i).toDouble()));
  }
  return vector;
}

bool Json::contains(std::string key) {
  return QJsonObject::contains(QString::fromStdString(key));
}

std::vector<std::string> Json::getKeys(void) {
  std::vector<QString> qstringKeys = keys().toVector().toStdVector();
  std::vector<std::string> keys;
  for(int currentKey = 0; currentKey < qstringKeys.size(); currentKey++) {
    keys.push_back(qstringKeys[currentKey].toStdString());
  }
  return keys;
}

QJsonValue Json::takeFromJson(std::string key) {
  return take(QString::fromStdString(key));
}
