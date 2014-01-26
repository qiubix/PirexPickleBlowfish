#include "ViewController.hpp"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent) {

}

void ViewController::fieldClicked(void) {
  qDebug() << "Field on board Clicked.";
}

void ViewController::handFieldClicked(int player, int whichToken) {
  qDebug() << "Hand field number: " << whichToken << " of player: " << player << " Clicked.";
}
