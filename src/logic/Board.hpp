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
  void linkMiddleRing();
  void createOutsideRing(void);
  void linkOutsideRing();
  Side getOppositeEdge(Side edge);
  Side incrementEdge(Side edge);
  Side decrementEdge(Side edge);

  std::vector <Field* > fields;
  Field* middle;
};

#endif //BOARD_HPP
