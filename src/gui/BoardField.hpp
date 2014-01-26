#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include "Hexagon.hpp"

class BoardField : public Hexagon
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  BoardField(float radius = 50, QGraphicsItem *parent = 0);

signals:
  void fieldClicked(void);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // BOARDFIELD_H
