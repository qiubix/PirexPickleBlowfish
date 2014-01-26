#include "Board.hpp"

Board::Board(QGraphicsItem* parent) : QGraphicsItem(parent)
{
  field = new Field(50, this);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  Q_UNUSED(painter)
}

QRectF Board::boundingRect() const {
  return QRectF(0, 0, 0, 0);
}
