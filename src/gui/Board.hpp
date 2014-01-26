#ifndef BOARD_HPP
#define BOARD_HPP

#include <QGraphicsItem>
#include <QPainter>

#include "Field.hpp"

class Board : public QGraphicsItem
{
public:
  Board(QGraphicsItem* parent = 0);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;
  Field* field;

};

#endif // BOARD_HPP
