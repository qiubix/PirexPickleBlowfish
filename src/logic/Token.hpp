#ifndef TOKEN_HPP
#define TOKEN_HPP

enum Army {
  MOLOCH,
  BORGO,
  OUTPOST,
  HEGEMONY
};

class Token
{
  Army army;
public:
  Army getArmy();
};

#endif //TOKEN_HPP
