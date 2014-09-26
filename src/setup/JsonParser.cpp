#include "JsonParser.hpp"

#include <QFile>
#include <QJsonDocument>

JsonParser * JsonParser::instance = nullptr;

JsonParser * JsonParser::getInstance()
{
  if(instance == nullptr) {
    instance = new JsonParser();
  }
  return instance;
}

JsonParser::JsonParser() {
}

Json* JsonParser::parse(std::string fileName) {
  QFile jsonFile;
  jsonFile.setFileName(QString::fromStdString(fileName));
  jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QByteArray fileJsonData = jsonFile.readAll();
  jsonFile.close();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(fileJsonData);
  return new Json(jsonDocument.object());
}
