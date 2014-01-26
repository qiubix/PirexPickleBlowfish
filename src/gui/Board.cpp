#include "Board.hpp"
#include <QtCore/qmath.h>
#include <QDebug>

Board::Board(ViewController* controller, QGraphicsItem* parent) : QGraphicsItem(parent)
{
  float radius = 50;
  float x = 0;
  float y = 0;
  float xSpacing = 5;
  float ySpacing = 3;
  float xDiff = 1.5 * radius + xSpacing;
  float yDiff = qSqrt(3) * radius/2+ ySpacing;
  Field * field;
  int counter = 0;

  counter++;
  field = new Field(radius, this);
  field -> setPos(x, y);
  QObject::connect(field, SIGNAL(fieldClicked()), controller, SLOT(fieldClicked()));
  for(int j = 0; j <= 2; j++) {
    for(int i = 0; i < 6; i++) {
      for(int k = 0; k < j; k++) {
        counter++;
        field = new Field(radius, this);
        field -> setPos(x, y);
        QObject::connect(field, SIGNAL(fieldClicked()), controller, SLOT(fieldClicked()));
        changeCoordinates(x, y, xDiff, yDiff, i);
      }
    }
    changeCoordinates(x, y, xDiff, yDiff, 4);
  }
}

void Board::changeCoordinates(float& x, float& y, float xDiff, float yDiff, int numberHardToName) {
  int yMultiplier = 1;
  if(numberHardToName >= 3)
    yMultiplier *= -1;
  if(numberHardToName % 3 == 1)
    yMultiplier *= 2;

  int xMultiplier = 1;
  switch(numberHardToName) {
  case 0: case 5:
    xMultiplier *= -1; break;
  case 1: case 4:
    xMultiplier = 0; break;
  }

  x += xDiff * xMultiplier;
  y += yDiff * yMultiplier;
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  Q_UNUSED(painter)
}

QRectF Board::boundingRect() const {
  return QRectF(0, 0, 0, 0);
}
