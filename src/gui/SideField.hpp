#ifndef SIDE_FIELD_H
#define SIDE_FIELD_H

#include "Hexagon.hpp"

class SideField : public Hexagon
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  SideField(float radius = 50, QGraphicsItem *parent = 0);

signals:
  void fieldClicked(void);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // SIDE_FIELD_H

