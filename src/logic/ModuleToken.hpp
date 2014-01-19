#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include <vector>
#include "Module.hpp"

class ModuleToken : public Module
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes, Side* activeEdges);
  ~ModuleToken() {}

  void addBoardToken(BoardToken* token, Side edge);
  void removeBoardToken(BoardToken* token, Side edge);

private:
  std::vector<BoardToken*> boardTokens;
  Side* activeEdges;

  bool isEdgeActive(Side edge);
};

#endif //MODULETOKEN_HPP
