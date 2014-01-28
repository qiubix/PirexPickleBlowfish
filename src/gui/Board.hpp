#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

#include <QGraphicsItem>
#include <QPainter>

#include "ViewController.hpp"
#include "logic/Field.hpp"

namespace gui {
  class Board : public QGraphicsItem
  {
  public:
    Board(ViewController* controller, Field* middleField, QGraphicsItem* parent = 0);

  protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void changeCoordinates(float& x, float& y, float xDiff, float yDiff, int numberHardToName);

  };
}

#endif // GUI_BOARD_HPP
