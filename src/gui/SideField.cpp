#include "SideField.hpp"

SideField::SideField(float radius, QGraphicsItem* parent) : Hexagon(radius, parent)
{
}

void SideField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked();
}
