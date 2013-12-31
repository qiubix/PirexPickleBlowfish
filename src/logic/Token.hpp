#ifndef TOKEN_HPP
#define TOKEN_HPP

//REVIEW: I suggest enums' names begin with capital letter
//REVIEW: Do we want to have these polish enums in our code? it is better to have only english because we don't display this to a user.
//REVIEW: I think that enums are better written in few line not just one but it's good as it is maybe.
enum army { MOLOCH, BORGO, POSTERUNEK, HEGEMONIA }; //REVIEW: there should be a line after this enum.
class Token
{
  army affiliation; //REVIEW: why not just Army army? If you look at this from outside and you have getAffiliation method it doesn't say what affiliation it is.
public:
  army getAffiliation();
};

#endif //TOKEN_HPP
