#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"

//TODO: implement methods
//TODO: add methods implementing game's rules, checking if particular play is valid
class Controller
{
public:
  Controller(Model* model);

  Board *getModelBoard();
  void initializeNewPlayer(Army army);
  void drawTokensForActivePlayer();

  void setGameState(GameState newState);
  void startBattle();
  void rotateClockwise(BoardToken* token);
  void rotateAnticlockwise(BoardToken* token);
  void putOnBoard(BoardToken* token, Field* field);
  void move(BoardToken* token, Field* destination);
  void strikeToken(BoardToken* token, int strength);
  void bombStrikeField(Field* epicentrum);
  void destroy(BoardToken* token);
  void reset();

private:
  Model* model;
  int getRandomNumber(int i);
};

#endif //CONTROLLER_HPP
