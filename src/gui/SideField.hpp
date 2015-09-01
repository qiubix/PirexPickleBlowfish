#ifndef SIDE_FIELD_H
#define SIDE_FIELD_H

#include "Hexagon.hpp"

class SideField : public Hexagon
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  SideField(int player, int whichToken, float radius = 50, QGraphicsItem *parent = 0);

  int getPlayer();
  int getWhichToken();

signals:
  void fieldClicked(SideField*);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  int player;
  int whichToken;

};

#endif // SIDE_FIELD_H

