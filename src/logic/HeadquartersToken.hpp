#ifndef HEADQUARTERSTOKEN_HPP
#define HEADQUARTERSTOKEN_HPP

#include "UnitToken.hpp"
#include "ModuleToken.hpp"

static Side hqSides[] = {NORTH, NORTH_WEST, NORTH_EAST, SOUTH, SOUTH_WEST, SOUTH_EAST};
static std::vector<Side> HQ_EDGES(hqSides, hqSides+sizeof(hqSides)/sizeof(Side));

class HeadquartersToken : public UnitToken, public ModuleToken
{
public:
  //TODO: default NULL attributes, passed to constructors of base classes.
  HeadquartersToken(Army army, std::string name, Attributes* attributes, std::vector<Side> edges = HQ_EDGES);
  ~HeadquartersToken() {}
};

#endif //HEADQUARTERSTOKEN_HPP
