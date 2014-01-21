#include "Controller.hpp"

//TODO: implement
Controller::Controller(Model* model)
  : model(model) {}

void Controller::setGameState(GameState newState)
{
  model->setGameState(newState);
}

void Controller::activate(BoardToken* token)
{

}

void Controller::rotateClockwise(BoardToken* token)
{
  token->rotateClockwise();
}

void Controller::rotateAnticlockwise(BoardToken* token)
{
  token->rotateAnticlockwise();
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

void Controller::strikeSurroundingTokens(Field* epicentrum)
{

}

void Controller::destroy(BoardToken* token)
{

}

void Controller::reset()
{

}
