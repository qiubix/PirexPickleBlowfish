#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include "BoardToken.hpp"

class ModuleToken : public BoardToken
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes);
  ~ModuleToken() {}
};

#endif //MODULETOKEN_HPP
