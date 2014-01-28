#include "SideField.hpp"

SideField::SideField(int player, int whichToken, float radius, QGraphicsItem* parent)
  : Hexagon(radius, parent), player(player), whichToken(whichToken)
{
}

int SideField::getPlayer(void) {
  return player;
}

int SideField::getWhichToken(void) {
  return whichToken;
}

void SideField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked(this);
}
