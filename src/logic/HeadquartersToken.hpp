#ifndef HEADQUARTERSTOKEN_HPP
#define HEADQUARTERSTOKEN_HPP

#include "UnitToken.hpp"
#include "ModuleToken.hpp"

class HeadQuartersToken : public UnitToken, public ModuleToken
{
public:
  HeadQuartersToken(Army army, std::string name, Attributes* attributes, std::vector<Side> edges);
  ~HeadQuartersToken() {}
};

#endif //HEADQUARTERSTOKEN_HPP
