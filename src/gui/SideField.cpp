#include "SideField.hpp"

SideField::SideField(int player, int whichToken, float radius, QGraphicsItem* parent)
  : Hexagon(radius, parent), player(player), whichToken(whichToken)
{
}

void SideField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked(player, whichToken);
}
