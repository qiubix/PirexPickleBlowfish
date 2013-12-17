#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "logic/Dollar.hpp"
#include "gui/MainWindowSample.hpp"

void mainWindowInit(QApplication* app)
{
  MainWindowSample* mainWindowSample = new MainWindowSample;
  QObject::connect (mainWindowSample->getQuitGameButton(), SIGNAL(clicked()), app, SLOT(quit()));
  mainWindowSample->show();
}

void dollarInit(void)
{
  Dollar* dollar = new Dollar(5);
  dollar->times(2);
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  mainWindowInit(&app);
  dollarInit();
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}
