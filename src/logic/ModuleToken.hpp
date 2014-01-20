#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include <vector>
#include "Module.hpp"

class ModuleToken : public Module
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes, std::vector<Side> activeEdges);
  virtual ~ModuleToken() {}

  void addBoardToken(BoardToken* token);
  void removeBoardToken(BoardToken* token);

  bool isEdgeActive(Side edge);

private:
  std::vector<BoardToken*> boardTokens;
  std::vector<Side> activeEdges;
};

#endif //MODULETOKEN_HPP
