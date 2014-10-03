#include "ModuleToken.hpp"

ModuleToken::ModuleToken(Army army, std::string name, Attributes* attributes, std::vector<Side> activeEdges)
  : Module(army, name, attributes)
{
  this -> activeEdges = activeEdges;
}

void ModuleToken::addBoardToken(BoardToken* token)
{
  boardTokens.push_back(token);
}

void ModuleToken::removeBoardToken(BoardToken* token)
{
  for (auto it = boardTokens.begin(); it != boardTokens.end(); ++it) {
    if (*it == token) {
      boardTokens.erase(it);
      break;
    }
  }
}

bool ModuleToken::isEdgeActive(Side edge)
{
  //TODO: checking orientation and comparing to global reference
  for (int i=0; i<activeEdges.size(); ++i) {
    if (activeEdges[i] == edge) {
      return true;
    }
  }
  return false;
}
