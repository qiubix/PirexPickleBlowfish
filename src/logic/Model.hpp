#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include "Board.hpp"
#include "BoardToken.hpp"
#include "Player.hpp"

//TODO: figure out proper game states
enum GameState {
  GAME,
  PAUSE
};

class Model
{
public:
  Model(void);
  ~Model(void) {}

  //getters
  Board* getBoard(void);
  GameState getGameState(void);
  Player* getCurrentPlayer(void);

  void setGameState(GameState newState);
  void moveToNextPlayer(void);

private:
  Board* board;
  GameState gameState;
  std::vector <Token*> usedTokens;
  std::vector <Player*> players;
  Player* currentPlayer;
};

#endif //MODEL_HPP
