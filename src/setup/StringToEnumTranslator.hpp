#ifndef STRING_TO_ENUM_TRANSLATOR_HPP
#define STRING_TO_ENUM_TRANSLATOR_HPP

#include "logic/Token.hpp"
#include "logic/BoardToken.hpp"

#include <map>
#include <string>

class StringToEnumTranslator
{
public:
  static StringToEnumTranslator * getInstance();

  Army getArmy(std::string army);
  AttributeName getAttributeName(std::string attribute);

protected:
  StringToEnumTranslator();

private:
  static StringToEnumTranslator * instance;

  std::map<std::string, Army> armiesDictionary;
  std::map<std::string, AttributeName> attributesDictionary;

};

#endif // STRING_TO_ENUM_TRANSLATOR_HPP
