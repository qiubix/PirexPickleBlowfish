#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

//TODO: introduce c++11 enums
//http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
enum Army {
  MOLOCH,
  BORGO,
  OUTPOST,
  HEGEMONY
};

class Token
{
public:
  Token(Army army, std::string name);

  //getters
  Army getArmy(void);
  std::string getName(void);

private:
  Army army;
  std::string name;
};

#endif //TOKEN_HPP
