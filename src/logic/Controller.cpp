#include "Controller.hpp"

//TODO: implement
Controller::Controller(Model* model)
  : model(model) {}

void Controller::setGameState(GameState newState)
{
  model->setGameState(newState);
}

void Controller::reset()
{

}

void Controller::rotate(BoardToken* token)
{

}

void Controller::move(BoardToken* token)
{

}

void Controller::pushToken(BoardToken* pusher, BoardToken* pushee)
{

}

void Controller::generateNewTokens()
{

}

void Controller::drawTokens(Player* player)
{

}

void Controller::strikeToken(BoardToken* token, int strength)
{

}

void Controller::strikeSurroundingTokens(BoardToken* epicentrum)
{

}
