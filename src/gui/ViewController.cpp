#include "ViewController.hpp"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent) {

}

void ViewController::fieldClicked(void) {
  qDebug() << "field clicked in controller.";
}
