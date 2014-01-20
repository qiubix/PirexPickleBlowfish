#include "Json.hpp"

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
    vector.push_back(array.at(i).toObject());
  }
  return vector;
}

Json Json::getObject(std::string key) {
  return Json(takeFromJson(key).toObject());
}

QJsonValue Json::takeFromJson(std::string key) {
  return take(QString::fromStdString(key));
}
