#include "BoardField.hpp"

BoardField::BoardField(float radius, QGraphicsItem* parent) : Hexagon(radius, parent)
{
}

void BoardField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked();
}
