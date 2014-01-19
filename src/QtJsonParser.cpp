#include "QtJsonParser.hpp"

#include <QFile>
#include <QJsonDocument>

QtJsonParser::QtJsonParser() {
  json = new JsonType();
}

QtJsonParser::QtJsonParser(Json* json) : JsonParser() {
  this -> json = dynamic_cast<JsonType*>(json);
}

QtJsonParser::~QtJsonParser() {
  delete json;
}

std::string QtJsonParser::getStringValue(std::string key) {
  return json -> getStringValue(key);
}

int QtJsonParser::getIntegerValue(std::string key) {
  return json -> getIntegerValue(key);
}

bool QtJsonParser::getBooleanValue(std::string key) {
  return json -> getBooleanValue(key);
}

void QtJsonParser::readJsonFromFile(std::string fileName) {
  QFile jsonFile;
  jsonFile.setFileName(QString::fromStdString(fileName));
  jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QByteArray fileJsonData = jsonFile.readAll();
  jsonFile.close();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(fileJsonData);
  json = new JsonType(jsonDocument.object());
}

void QtJsonParser::writeJsonToFile(std::string fileName) {

}
