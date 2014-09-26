#include "Board.hpp"

Board::Board() {
  middle = new Field;
  fields.push_back(middle);
  createMiddleRing();
  createOutsideRing();
}

Board::~Board() {
  //TODO: free memory
}

Field* Board::getMiddleField() {
  return middle;
}

void Board::createMiddleRing() {
  Side side = Side::NORTH;
  do {
    Field* newField = new Field;
    middle -> addNeighbour(newField, side);
    newField -> addNeighbour(middle, !side);
    fields.push_back(newField);
    ++side;
  } while (side != Side::NORTH);
  linkMiddleRing();
}

void Board::linkMiddleRing() {
  Side ringEdge = Side::SOUTH_EAST;
  Side centerEdge = Side::NORTH;
  Field* current = middle -> getNeighbour(centerEdge);
  Field* next = current -> getNeighbour(ringEdge);
  while (next == NULL) {
    ++centerEdge;
    next = middle -> getNeighbour(centerEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, !ringEdge);
    current = next;
    ++ringEdge;
    next = current -> getNeighbour(ringEdge);
  }
}

//FIXME: incrementation side effects - should pass value as argument, not reference
void Board::createOutsideRing() {
  Side side = Side::NORTH;
  do {
    Field* root = middle -> getNeighbour(side);
    Field* first = new Field;
    Field* second = new Field;
    root -> addNeighbour(first, side);
    root -> addNeighbour(second, ++side);
    --side;
    first -> addNeighbour(root, !side);
    second -> addNeighbour(root, !(++side));
    --side;
    fields.push_back(first);
    fields.push_back(second);
    ++side;
  } while (side != Side::NORTH);
  linkOutsideRing();
}

void Board::linkOutsideRing() {
  Side ringEdge = Side::SOUTH_EAST;
  Side centerEdge = Side::NORTH;
  Side middleEdge = Side::NORTH;
  Field* current = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
  Field* next = current -> getNeighbour(ringEdge);
  while (next == NULL) {
    ++middleEdge;
    next = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, !ringEdge);
    current = next;
    ++centerEdge;
    next = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, !ringEdge);
    current = next;
    ++ringEdge;
    next = current -> getNeighbour(ringEdge);
  }
}
