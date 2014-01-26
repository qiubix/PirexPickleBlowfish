#include "Field.hpp"
#include <QtCore/qmath.h>
#include <QDebug>

Field::Field(float radius, QGraphicsItem *parent) : QObject(), QGraphicsItem(parent)
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

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter -> setBrush(Qt::red);
  painter -> drawPolygon(polygon);
}

QRectF Field::boundingRect() const {
  return QRectF(-radius, -height/2, width, height);
}

QPainterPath Field::shape() const {
  QPainterPath path;
  path.addPolygon(polygon);
  return path;
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
  emit fieldClicked();
  qDebug() << "Hexagon clicked.";
}
