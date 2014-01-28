#include "Board.hpp"
#include <QtCore/qmath.h>
#include <QDebug>

#include "BoardField.hpp"
#include "SideField.hpp"

namespace gui {

Board::Board(ViewController* controller, Field* middleField, QGraphicsItem* parent) : QGraphicsItem(parent)
{
  float radius = 50;
  float x = 0;
  float y = 0;
  float xSpacing = 5;
  float ySpacing = 3;
  float xDiff = 1.5 * radius + xSpacing;
  float yDiff = qSqrt(3) * radius/2+ ySpacing;
  BoardField * boardField;
  int counter = 0;
  Field * currentField = middleField;
  Side currentSide = SOUTH_WEST;

  //TODO: clean this mess
  //TODO: change to clockwise (easier with currentSide)
  counter++;
  boardField = new BoardField(currentField, radius, this);
  boardField -> setPos(x, y);
  QObject::connect(boardField, SIGNAL(fieldClicked(BoardField*)), controller, SLOT(fieldClicked(BoardField*)));
  for(int j = 0; j <= 2; j++) {
    for(int i = 0; i < 6; i++) {
      for(int k = 0; k < j; k++) {
        counter++;
        boardField = new BoardField(currentField, radius, this);
        boardField -> setPos(x, y);
        QObject::connect(boardField, SIGNAL(fieldClicked(BoardField*)), controller, SLOT(fieldClicked(BoardField*)));
        changeCoordinates(x, y, xDiff, yDiff, i);
        currentField = currentField -> getNeighbour(currentSide);
        if(k == j - 1) {
          currentSide = static_cast<Side>((currentSide + 5) % 6);
        }
      }
    }
    changeCoordinates(x, y, xDiff, yDiff, 4);
    currentField = currentField -> getNeighbour(NORTH);
  }

  SideField * sideField;
  y = -2 * yDiff;
  x = -6 * radius;
  for(int j = 0; j < 2; j++) {
    for(int i = 0; i < 3; i++) {
      sideField = new SideField(j, i, radius, this);
      sideField -> setPos(x,y);
      QObject::connect(sideField, SIGNAL(fieldClicked(SideField*)), controller, SLOT(handFieldClicked(SideField*)));
      y += 2 * yDiff;
    }
    y = -2 * yDiff;
    x = 6 * radius;
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

}//: namespace gui
