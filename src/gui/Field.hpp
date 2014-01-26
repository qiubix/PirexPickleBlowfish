#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>
#include <QPainter>

class Field : public QObject, public QGraphicsItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  Field(QGraphicsItem *parent = 0);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;

  int width;
};

#endif // FIELD_HPP
