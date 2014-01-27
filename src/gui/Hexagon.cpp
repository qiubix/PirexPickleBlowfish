#include "Hexagon.hpp"
#include <QtCore/qmath.h>
#include <QDebug>

Hexagon::Hexagon(float radius, QGraphicsItem *parent) : QObject(), QGraphicsItem(parent)
{
  this -> radius = radius;
  this -> width = 2 * radius;
  this -> height = qSqrt(3) * radius;

  this -> polygon << QPoint(-radius, 0);
  this -> polygon << QPoint(-radius/2, height/2);
  this -> polygon << QPoint(radius/2, height/2);
  this -> polygon << QPoint(radius, 0);
  this -> polygon << QPoint(radius/2, -height/2);
  this -> polygon << QPoint(-radius/2, -height/2);
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter -> setBrush(Qt::red);
  painter -> drawPolygon(polygon);
}

QRectF Hexagon::boundingRect() const {
  return QRectF(-radius, -height/2, width, height);
}

QPainterPath Hexagon::shape() const {
  QPainterPath path;
  path.addPolygon(polygon);
  return path;
}
