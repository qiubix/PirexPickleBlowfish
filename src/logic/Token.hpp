#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "Attribute.hpp"
#include "Army.hpp"

class Token
{
public:
  Token(Army army, std::string name);
  virtual ~Token() {}

  //getters
  Army getArmy();
  std::string getName();

protected:
  Attribute* army;

private:
  std::string name;
};

#endif //TOKEN_HPP
