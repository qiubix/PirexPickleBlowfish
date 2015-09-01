#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Field.hpp"

class Board
{
public:
  Board();
  ~Board();
  Field *getMiddleField();

private:
  void createMiddleRing();
  void linkMiddleRing();
  void createOutsideRing();
  void linkOutsideRing();

  std::vector <Field* > fields;
  Field* middle;
};

#endif //BOARD_HPP
