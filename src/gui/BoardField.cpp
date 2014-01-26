#include "BoardField.hpp"

BoardField::BoardField(Field* field, float radius, QGraphicsItem* parent)
  : Hexagon(radius, parent), field(field)
{
}

void BoardField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked(field);
}
