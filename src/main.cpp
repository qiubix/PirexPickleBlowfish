#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "gui/MainWindowSample.hpp"
#include "Logger.hpp"

void mainWindowInit(QApplication* app)
{
  MainWindowSample* mainWindowSample = new MainWindowSample;
  QObject::connect (mainWindowSample->getQuitGameButton(), SIGNAL(clicked()), app, SLOT(quit()));
  mainWindowSample->show();
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
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}
