#include "Field.hpp"
#include <QtCore/qmath.h>

Field::Field(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent)
{
  width = 100;
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter -> setBrush(Qt::red);

  float d = 50.0;

  QPolygonF polygon;
  polygon << QPoint(-d, 0);
  polygon << QPoint(-d/2, qSqrt(3)*d/2);
  polygon << QPoint(d/2, qSqrt(3)*d/2);
  polygon << QPoint(d, 0);
  polygon << QPoint(d/2, -qSqrt(3)*d/2);
  polygon << QPoint(-d/2, -qSqrt(3)*d/2);
  painter -> drawPolygon(polygon);
}

QRectF Field::boundingRect() const {
  return QRectF(-width/2, -width/2, width, width);
}
