#ifndef BOARD_HPP
#define BOARD_HPP

#include <QGraphicsItem>
#include <QPainter>

#include "Field.hpp"
#include "ViewController.hpp"

class Board : public QGraphicsItem
{
public:
  Board(ViewController* controller, QGraphicsItem* parent = 0);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;

  Field* field;

  void changeCoordinates(float& x, float& y, float xDiff, float yDiff, int numberHardToName);

};

#endif // BOARD_HPP
