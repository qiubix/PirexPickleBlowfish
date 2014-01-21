#ifndef STRING_TO_ENUM_TRANSLATOR_HPP
#define STRING_TO_ENUM_TRANSLATOR_HPP

#include "logic/Token.hpp"

#include <map>
#include <string>

class StringToEnumTranslator
{
public:
  static StringToEnumTranslator * getInstance();

  Army getArmy(std::string army);

protected:
  StringToEnumTranslator();

private:
  static StringToEnumTranslator * instance;

  std::map<std::string, Army> armiesDictionary;
};

#endif // STRING_TO_ENUM_TRANSLATOR_HPP
