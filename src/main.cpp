#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "logic/Dollar.hpp"
#include "gui/MainWindowSample.hpp"

//REVIEW: i know this is the transitional make but we should extract code into meaningful methods
//here for example: mainWindowInit and dollarInit or something like that
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindowSample mainWindowSample;
  QObject::connect (mainWindowSample.getQuitGameButton(), SIGNAL(clicked()), &app, SLOT(quit()));
  mainWindowSample.show();
  Dollar* dollar = new Dollar(5);
  dollar->times(2);
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}
