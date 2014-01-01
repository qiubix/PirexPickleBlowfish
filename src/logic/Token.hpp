#ifndef TOKEN_HPP
#define TOKEN_HPP

//REVIEW: I read something about enums in c++11, it seems that it is better to use strong typed enums
//http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
//but in this place it is okay but maybe in other places the new covention would be better, so for better code cohesion
enum Army {
  MOLOCH,
  BORGO,
  OUTPOST,
  HEGEMONY
};

//REVIEW: I think that token name is another good field in this class that we never thought about but i'm not sure we need it here
//but in fact name of token seems good even at least for logging or something
//REVIEW: same comment according to sections naming and order as in BoardToken class (forgot it last time)
class Token
{
  Army army;
public:
  Army getArmy();
};

#endif //TOKEN_HPP
