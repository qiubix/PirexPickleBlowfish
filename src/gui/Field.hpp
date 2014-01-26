#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>
#include <QPainter>

class Field : public QObject, public QGraphicsItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  Field(float radius = 50, QGraphicsItem *parent = 0);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;
  QPainterPath shape() const;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  float radius;
  float width;
  float height;
  QPolygonF polygon;
};

#endif // FIELD_HPP
