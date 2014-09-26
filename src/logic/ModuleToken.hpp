#ifndef MODULETOKEN_HPP
#define MODULETOKEN_HPP

#include <gtest/gtest.h>
#include <vector>
#include "Module.hpp"

class ModuleToken : public Module
{
public:
  ModuleToken(Army army, std::string name, Attributes* attributes = nullptr, std::vector<Side> activeEdges = NULL);
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
