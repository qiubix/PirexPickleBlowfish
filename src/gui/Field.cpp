#include "Field.hpp"

Field::Field(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent)
{
  width = 100;
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter -> setBrush(Qt::yellow);
  painter -> drawEllipse(-width/2, -width/2, width, width);
}

QRectF Field::boundingRect() const {
  return QRectF(-width/2, -width/2, width, width);
}
