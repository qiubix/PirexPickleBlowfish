#include "ViewController.hpp"
#include <QDebug>

ViewController::ViewController(Controller* modelController, QObject *parent) : QObject(parent) {
  this -> modelController = modelController;
}

void ViewController::fieldClicked(BoardField* field) {
  qDebug() << "Field on board Clicked. Pointer: " << field->getField();
  field -> setImageAndRotation("armies/moloch/headquarters.png", (1 % 6 )*60);
}

void ViewController::handFieldClicked(SideField* field) {
  qDebug() << "Hand field number: " << field->getWhichToken() << " of player: " << field->getPlayer() << " Clicked.";
  field -> setImageAndRotation("armies/moloch/headquarters.png", (1 % 6 )*60);
}
