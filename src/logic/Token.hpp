#ifndef TOKEN_HPP
#define TOKEN_HPP

enum army { MOLOCH, BORGO, POSTERUNEK, HEGEMONIA };
class Token
{
  army affiliation;
public:
  army getAffiliation();
};

#endif //TOKEN_HPP
