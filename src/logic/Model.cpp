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
