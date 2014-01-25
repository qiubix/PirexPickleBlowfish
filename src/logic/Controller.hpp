#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"

//TODO: implement methods
//TODO: add methods implementing game's rules, checking if particular play is valid
class Controller
{
public:
  Controller(Model* model);
  ~Controller(void) {}

  void setGameState(GameState newState);
  void activate(BoardToken* token);
  void rotateClockwise(BoardToken* token);
  void rotateAnticlockwise(BoardToken* token);
  void putOnBoard(BoardToken* token, Field* field);
  void move(BoardToken* token, Field* destination);
  void pushToken(BoardToken* pusher, BoardToken* pushee);
  void generateNewTokens(void);
  void drawTokens(Player* player);
  void strikeToken(BoardToken* token, int strength);
  void bombStrikeField(Field* epicentrum);
  void destroy(BoardToken* token);
  void reset(void);

private:
  Model* model;
};

#endif //CONTROLLER_HPP
