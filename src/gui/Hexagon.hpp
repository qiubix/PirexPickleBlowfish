#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <QGraphicsItem>
#include <QPainter>

class Hexagon : public QObject, public QGraphicsItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  Hexagon(float radius = 50, QGraphicsItem *parent = 0);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;
  QPainterPath shape() const;

  float radius;
  float width;
  float height;
  QPolygonF polygon;
};

#endif // HEXAGON_HPP
