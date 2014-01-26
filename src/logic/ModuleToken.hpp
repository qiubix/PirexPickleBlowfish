#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include <gtest/gtest.h>
#include <vector>
#include "Module.hpp"

static Side moduleSides[] = {NORTH};
static std::vector<Side> MODULE_EDGES(moduleSides, moduleSides+sizeof(moduleSides)/sizeof(Side));

class ModuleToken : public Module
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes, std::vector<Side> activeEdges = MODULE_EDGES);
  virtual ~ModuleToken() {}

  void addBoardToken(BoardToken* token);
  void removeBoardToken(BoardToken* token);

  bool isEdgeActive(Side edge);

private:
  std::vector<BoardToken*> boardTokens;
  std::vector<Side> activeEdges;

  FRIEND_TEST(ModuleTokenTest, shouldAddBoardToken);
  FRIEND_TEST(ModuleTokenTest, shouldRemoveBoardToken);
};

#endif //MODULETOKEN_HPP
