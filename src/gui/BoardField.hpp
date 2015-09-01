#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include "Hexagon.hpp"
#include "logic/Field.hpp"

class BoardField : public Hexagon
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  BoardField(Field* field, float radius = 50, QGraphicsItem *parent = 0);

  Field *getField();

signals:
  void fieldClicked(BoardField*);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  Field* field;

};

#endif // BOARDFIELD_H
