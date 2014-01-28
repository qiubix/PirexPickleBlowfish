#include "Controller.hpp"
#include "setup/GameBox.hpp"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

//TODO: implement
Controller::Controller(Model* model)
  : model(model) {
}

Board* Controller::getModelBoard() {
  return model -> getBoard();
}

//TODO: write test
void Controller::initializeNewPlayer(Army army) {
  Player* player = new Player(army);
  std::vector<Token*> tokens = GameBox::getInstance() -> getArmy(army);
  std::random_shuffle (tokens.begin(), tokens.end());
  player -> addTokens(tokens);
  model -> addPlayer(player);
}

void Controller::setGameState(GameState newState) {
  model -> setGameState(newState);
}

void Controller::startBattle() {
  //TODO: implement
}

void Controller::rotateClockwise(BoardToken* token) {
  token -> rotateClockwise();
}

void Controller::rotateAnticlockwise(BoardToken* token) {
  token -> rotateAnticlockwise();
}

void Controller::putOnBoard(BoardToken* token, Field* field) {
  field -> setToken(token);
  token -> setField(field);
  model -> getPlayer(token -> getArmy());
}

void Controller::move(BoardToken* token, Field* destination) {
  Field* oldField = token->getField();
  oldField -> setToken(NULL);
  token -> setField(destination);
  destination -> setToken(token);
}

void Controller::strikeToken(BoardToken* token, int strength) {
  Attribute* toughness = token -> getAttribute(TOUGHNESS);
  if (toughness != NULL) {
    toughness -> downgradeBy(strength);
  }
}

void Controller::bombStrikeField(Field* epicentrum) {
  BoardToken* token = dynamic_cast<BoardToken*>(epicentrum -> getToken());
  if(token != NULL) {
    token -> downgradeAttributeBy(TOUGHNESS);
  }
  Field* neighbour;
  for(int i=0; i<6; ++i) {
    neighbour = epicentrum -> getNeighbour((Side) i);
    if(neighbour != NULL && neighbour -> getToken() != NULL) {
      token = dynamic_cast<BoardToken*>(neighbour -> getToken());
      token -> downgradeAttributeBy(TOUGHNESS);
    }
  }
}

void Controller::destroy(BoardToken* token) {
  model -> killToken(token);
}

void Controller::reset(void) {
  model -> reset();
}

int Controller::getRandomNumber(int i) {
  return std::rand()%i;
}
