#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"

//TODO: implement methods
class Controller
{
public:
  Controller(Model* model);
  ~Controller(void) {}

  void setGameState(GameState newState);
  void activate(BoardToken* token);
  void rotateClockwise(BoardToken* token);
  void rotateAnticlockwise(BoardToken* token);
  void move(BoardToken* token);
  void pushToken(BoardToken* pusher, BoardToken* pushee /*(pussy)*/);
  void generateNewTokens(void);
  void drawTokens(Player* player);
  void strikeToken(BoardToken* token, int strength);
  void strikeSurroundingTokens(Field* epicentrum);
  void destroy(BoardToken* token);
  void reset(void);

private:
  Model* model;
};

#endif //CONTROLLER_HPP
