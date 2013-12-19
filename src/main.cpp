#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "logic/Dollar.hpp"
#include "gui/MainWindowSample.hpp"
#include "Logger.hpp"

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
  initLogging();

  LOG(trace) << "A trace severity message";
  LOG(debug) << "A debug severity message";
  LOG(info) << "An informational severity message";
  LOG(warning) << "A warning severity message";
  LOG(error) << "An error severity message";
  LOG(fatal) << "A fatal severity message";

  QApplication app(argc, argv);
  mainWindowInit(&app);
  dollarInit();
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}
