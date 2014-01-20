#include "Model.hpp"

Model::Model()
  : gameState(PAUSE) {}

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

}

void Model::setGameState(GameState newState)
{
  gameState = newState;
}

void Model::moveToNextPlayer()
{

}
