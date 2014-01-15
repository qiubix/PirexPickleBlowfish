#include "ModuleToken.hpp"

ModuleToken::ModuleToken(Army army, std::string name, Attributes* attributes)
  : Module(army, name, attributes)
{
}

void ModuleToken::addBoardToken(BoardToken* token)
{
  boardTokens.push_back(token);
}

void ModuleToken::removeBoardToken(BoardToken* token)
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
