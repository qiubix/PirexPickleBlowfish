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
  Player* player = model->getCurrentPlayer();
  player->activateToken(token);
}

void Controller::rotateClockwise(BoardToken* token)
{
  token->rotateClockwise();
}

void Controller::rotateAnticlockwise(BoardToken* token)
{
  token->rotateAnticlockwise();
}

void Controller::putOnBoard(BoardToken* token, Field* field)
{
  field->setToken(token);
  token->setField(field);
}

void Controller::move(BoardToken* token, Field* destination)
{
  Field* oldField = token->getField();
  oldField->setToken(NULL);
  token->setField(destination);
  destination->setToken(token);
}

void Controller::pushToken(BoardToken* pusher, BoardToken* pushee)
{
  //TODO: implement
}

void Controller::generateNewTokens()
{
  //TODO: implement
}

void Controller::drawTokens(Player* player)
{
  //TODO: implement
}

void Controller::strikeToken(BoardToken* token, int strength)
{
  //TODO: implement
}

void Controller::bombStrikeField(Field* epicentrum)
{
  BoardToken* token = dynamic_cast<BoardToken*>(epicentrum->getToken());
  if(token != NULL) {
    token->downgradeAttributeBy(TOUGHNESS);
  }
  Field* neighbour;
  for(int i=0; i<6; ++i) {
    neighbour = epicentrum->getNeighbour((Side) i);
    if(neighbour != NULL && neighbour->getToken() != NULL) {
      token = dynamic_cast<BoardToken*>(neighbour->getToken());
      token->downgradeAttributeBy(TOUGHNESS);
    }
  }
}

void Controller::destroy(BoardToken* token)
{
  //TODO: check if token is in range for destruction
  model->killToken(token);
}

void Controller::reset(void)
{
  model->reset();
}
