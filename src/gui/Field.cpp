#include "Field.hpp"
#include <QtCore/qmath.h>
#include <QDebug>

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
  float d = 50.0;
  return QRectF(-d, -qSqrt(3)*d/2, 2*d, qSqrt(3)*d);
}

QPainterPath Field::shape() const {
  float d = 50.0;
  QPolygonF polygon;
  polygon << QPoint(-d, 0);
  polygon << QPoint(-d/2, qSqrt(3)*d/2);
  polygon << QPoint(d/2, qSqrt(3)*d/2);
  polygon << QPoint(d, 0);
  polygon << QPoint(d/2, -qSqrt(3)*d/2);
  polygon << QPoint(-d/2, -qSqrt(3)*d/2);
  QPainterPath p;
  p.addPolygon(polygon);
  return p;
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  qDebug() << "Hexagon clicked.";
}
