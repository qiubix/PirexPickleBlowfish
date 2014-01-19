#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "Json.hpp"

class JsonParser
{
public:
  static JsonParser * getInstance();

  Json* parse(std::string fileName);

protected:
  JsonParser();

private:
  static JsonParser * instance;
};

#endif // JSONPARSER_H
