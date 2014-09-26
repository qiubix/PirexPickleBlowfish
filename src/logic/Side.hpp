#ifndef SIDE_HPP
#define SIDE_HPP

enum class Side {
  NORTH,
  NORTH_EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  NORTH_WEST
};

inline Side& operator++(Side& side) {
  switch(side) {
  case Side::NORTH: 
    return side = Side::NORTH_EAST;
  case Side::NORTH_EAST: 
    return side = Side::SOUTH_EAST;
  case Side::SOUTH_EAST: 
    return side = Side::SOUTH;
  case Side::SOUTH: 
    return side = Side::SOUTH_WEST;
  case Side::SOUTH_WEST: 
    return side = Side::NORTH_WEST;
  case Side::NORTH_WEST: 
    return side = Side::NORTH;
  }
}

inline Side& operator--(Side& side) {
  switch(side) {
  case Side::NORTH: 
    return side = Side::NORTH_WEST;
  case Side::NORTH_WEST: 
    return side = Side::SOUTH_WEST;
  case Side::SOUTH_WEST: 
    return side = Side::SOUTH;
  case Side::SOUTH: 
    return side = Side::SOUTH_EAST;
  case Side::SOUTH_EAST: 
    return side = Side::NORTH_EAST;
  case Side::NORTH_EAST: 
    return side = Side::NORTH;
  }
}

inline Side operator!(Side side) {
//  return (Side) ((edge+3)%6);
  switch(side) {
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

#endif //SIDE_HPP
