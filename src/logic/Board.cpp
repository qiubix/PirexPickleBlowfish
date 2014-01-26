#include "Board.hpp"

Board::Board() {
  middle = new Field;
  fields.push_back(middle);
  createMiddleRing();
}

Board::~Board() {
  //TODO: free memory
}

Field* Board::getMiddleField() {
  return middle;
}

//TODO: refactor - ugly code
void Board::createMiddleRing() {
  for (int i=0; i<6; ++i) {
    Field* newField = new Field;
    middle -> addNeighbour(newField, (Side) i);
    int middleContactEdge = (i+3)%6;
    newField -> addNeighbour(middle, (Side) middleContactEdge);
    if (i>0) {
      Field* previousInRing = middle -> getNeighbour((Side) (i-1));
      int contactEdge = (middleContactEdge+1)%6;
      newField -> addNeighbour(previousInRing, (Side) contactEdge);
      contactEdge = (contactEdge+3)%6;
      previousInRing -> addNeighbour(newField, (Side) contactEdge);
    }
    fields.push_back(newField);
  }
  Field* northNeigbour = middle -> getNeighbour(NORTH);
  Field* northWestNeighbour = middle -> getNeighbour(NORTH_WEST);
  northNeigbour -> addNeighbour(northWestNeighbour, SOUTH_WEST);
  northWestNeighbour -> addNeighbour(northNeigbour, NORTH_EAST);
}
