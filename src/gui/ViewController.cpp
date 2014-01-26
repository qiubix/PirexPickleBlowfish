#include "ViewController.hpp"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent) {

}

void ViewController::fieldClicked(Field* field) {
  qDebug() << "Field on board Clicked. Pointer: " << field;
}

void ViewController::handFieldClicked(int player, int whichToken) {
  qDebug() << "Hand field number: " << whichToken << " of player: " << player << " Clicked.";
}
