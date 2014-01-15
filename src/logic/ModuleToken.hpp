#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include <vector>
#include "Module.hpp"

class ModuleToken : public Module
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes);
  ~ModuleToken() {}

  void addBoardToken(BoardToken* token);
  void removeBoardToken(BoardToken* token);

private:
  std::vector<BoardToken*> boardTokens;
};

#endif //MODULETOKEN_HPP
