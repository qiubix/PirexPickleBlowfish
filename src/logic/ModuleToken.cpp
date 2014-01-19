#include "ModuleToken.hpp"

ModuleToken::ModuleToken(Army army, std::string name, Attributes* attributes, Side* activeEdges)
  : Module(army, name, attributes)
{
  this->activeEdges = activeEdges;
}

void ModuleToken::addBoardToken(BoardToken* token, Side edge)
{
  if (isEdgeActive(edge)) {
    boardTokens.push_back(token);
  }
}

void ModuleToken::removeBoardToken(BoardToken* token, Side edge)
{
  std::string tokenName = token->getName();
  std::vector<BoardToken*>::iterator it = boardTokens.begin();
  for (;it != boardTokens.end(); ++it) {
    if ((*it)->getName() == tokenName) {
      boardTokens.erase(it);
      break;
    }
  }
}

bool ModuleToken::isEdgeActive(Side edge)
{
  for (int i=0; i<sizeof(activeEdges); ++i) {
    if (activeEdges[i] == edge) {
      return true;
    }
  }
  return false;
}
