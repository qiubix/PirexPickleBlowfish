#include "Model.hpp"

Model::Model()
  : gameState(PAUSE), currentPlayerId(-1) {}

Board* Model::getBoard()
{
  return board;
}

GameState Model::getGameState()
{
  return gameState;
}

Player* Model::getCurrentPlayer()
{
  if (players.empty()) {
    return NULL;
  }
  else {
    return players[currentPlayerId];
  }
}

Player* Model::getPlayer(Army army)
{
  for (unsigned i=0; i<players.size(); ++i) {
    if(players.at(i)->getArmy() == army) {
      return players.at(i);
    }
  }
  return NULL;
}

int Model::getPlayersQuantity()
{
  return players.size();
}

void Model::setGameState(GameState newState)
{
  gameState = newState;
}

void Model::addPlayer(Player* newPlayer)
{
  players.push_back(newPlayer);
  if (currentPlayerId == -1) {
    currentPlayerId = 0;
  }
}

void Model::moveToNextPlayer()
{
  currentPlayerId = (++currentPlayerId) % players.size();
}

void Model::destroy(BoardToken* token)
{
  Field* field = token->getField();
  if (field != NULL) {
    field->setToken(NULL);
  }
  token->setField(NULL);
  Player* player = getPlayer(token->getArmy());
  player->deactivateToken(token);
  usedTokens.push_back(token);
}

void Model::reset()
{
  gameState = PAUSE;
  players.clear();
  usedTokens.clear();
  currentPlayerId = -1;
}
