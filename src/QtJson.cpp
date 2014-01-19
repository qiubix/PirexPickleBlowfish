#include "QtJson.h"

QtJson::QtJson() : Json(), QJsonObject() {
}

QtJson::~QtJson() {
}

std::string QtJson::getStringValue(std::string key) {
  return this -> take(QString::fromStdString(key)).toString().toStdString();
}

int QtJson::getIntegerValue(std::string key) {
  return  static_cast<int>(this -> take(QString::fromStdString(key)).toDouble());
}

bool QtJson::getBooleanValue(std::string key) {
  return this -> take(QString::fromStdString(key)).toBool();
}

void QtJson::addStringValue(std::string key, std::string value) {
  this -> insert(QString::fromStdString(key), QJsonValue(QString::fromStdString(value)));
}

void QtJson::addIntegerValue(std::string key, int value) {
  this -> insert(QString::fromStdString(key), QJsonValue(value));
}

void QtJson::addBooleanValue(std::string key, bool value) {
  this -> insert(QString::fromStdString(key), QJsonValue(value));
}
