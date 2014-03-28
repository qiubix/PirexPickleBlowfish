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
  for (int i=0; i<6; ++i) {
    Field* newField = new Field;
    middle -> addNeighbour(newField, (Side) i);
    newField -> addNeighbour(middle, getOppositeEdge((Side) i));
    fields.push_back(newField);
  }
  linkMiddleRing();
}

void Board::linkMiddleRing() {
  Side ringEdge = Side::SOUTH_EAST;
  Side centerEdge = Side::NORTH;
  Field* current = middle -> getNeighbour(centerEdge);
  Field* next = current -> getNeighbour(ringEdge);
  while (next == NULL) {
    centerEdge = incrementEdge(centerEdge);
    next = middle -> getNeighbour(centerEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, getOppositeEdge(ringEdge));
    current = next;
    ringEdge = incrementEdge(ringEdge);
    next = current -> getNeighbour(ringEdge);
  }
}

void Board::createOutsideRing() {
  for (int i=0; i<6; ++i) {
    Field* root = middle -> getNeighbour((Side) i);
    Field* first = new Field;
    Field* second = new Field;
    root -> addNeighbour(first, (Side) i);
    root -> addNeighbour(second, incrementEdge((Side) i));
    first -> addNeighbour(root, getOppositeEdge((Side) i));
    second -> addNeighbour(root, getOppositeEdge(incrementEdge((Side) i)));
    fields.push_back(first);
    fields.push_back(second);
  }
  linkOutsideRing();
}

void Board::linkOutsideRing() {
  Side ringEdge = Side::SOUTH_EAST;
  Side centerEdge = Side::NORTH;
  Side middleEdge = Side::NORTH;
  Field* current = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
  Field* next = current -> getNeighbour(ringEdge);
  while (next == NULL) {
    middleEdge = incrementEdge(middleEdge);
    next = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, getOppositeEdge(ringEdge));
    current = next;
    centerEdge = incrementEdge(centerEdge);
    next = middle -> getNeighbour(centerEdge) -> getNeighbour(middleEdge);
    current -> addNeighbour(next, ringEdge);
    next -> addNeighbour(current, getOppositeEdge(ringEdge));
    current = next;
    ringEdge = incrementEdge(ringEdge);
    next = current -> getNeighbour(ringEdge);
  }
}

Side Board::getOppositeEdge(Side edge) {
//  return (Side) ((edge+3)%6);
  switch(edge) {
  case Side::NORTH: 
    return Side::SOUTH;
  case Side::NORTH_EAST: 
    return Side::SOUTH_WEST;
  case Side::SOUTH_EAST: 
    return Side::NORTH_WEST;
  case Side::SOUTH: 
    return Side::NORTH;
  case Side::SOUTH_WEST: 
    return Side::NORTH_EAST;
  case Side::NORTH_WEST: 
    return Side::SOUTH_EAST;
  }
}

Side Board::incrementEdge(Side edge) {
//  return (Side) ((edge+1)%6);
  return ++edge;
}

Side Board::decrementEdge(Side edge) {
//  if (edge == NORTH) {
//    return NORTH_WEST;
//  }
//  else {
//    return (Side) (edge-1);
//  }
  return --edge;
}
