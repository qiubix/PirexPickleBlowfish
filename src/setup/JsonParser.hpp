#ifndef JSON_PARSER_H
#define JSON_PARSER_H

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

#endif // JSON_PARSER_H
