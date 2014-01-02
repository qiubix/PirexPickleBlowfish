#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum Army {
  MOLOCH,
  BORGO,
  OUTPOST,
  HEGEMONY
};

class Token
{
public:
  Token(void);
  Token(std::string name);
  Army getArmy(void);
  std::string getName(void);
private:
  Army army;
  std::string name;
};

#endif //TOKEN_HPP
