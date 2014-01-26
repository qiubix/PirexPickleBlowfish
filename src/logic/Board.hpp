#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Field.hpp"

class Board
{
public:
  Board(void);
  ~Board(void);
  Field* getMiddleField(void);

private:
  void createMiddleRing(void);

  std::vector <Field* > fields;
  Field* middle;
};

#endif //BOARD_HPP
