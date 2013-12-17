#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "logic/Dollar.hpp"
#include "gui/MainWindowSample.hpp"

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
