#ifndef HEADQUARTERSTOKEN_HPP
#define HEADQUARTERSTOKEN_HPP

#include "Side.hpp"
#include "UnitToken.hpp"
#include "ModuleToken.hpp"

static Side hqSides[] = {Side::NORTH, Side::NORTH_WEST, Side::NORTH_EAST, Side::SOUTH, Side::SOUTH_WEST, Side::SOUTH_EAST};
static std::vector<Side> HQ_EDGES(hqSides, hqSides+sizeof(hqSides)/sizeof(Side));

//REVIEW: FIXME: such inheritance have negative consequences (duplicated BoardToken::attributes)
// one way is virtual inheritance, other overloading addAttribute and so on to call always UnitToken::addAttribute
// but the second way should be only temporal solution.
class HeadquartersToken : public UnitToken, public ModuleToken
{
public:
  HeadquartersToken(Army army, std::string name, Attributes* attributes = NULL, std::vector<Side> edges = HQ_EDGES);
  ~HeadquartersToken() {}
};

#endif //HEADQUARTERSTOKEN_HPP
