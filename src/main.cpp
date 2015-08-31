#include <QtWidgets>
#include <QObject>
#include <iostream>
#include <ctime>
#include "gui/MainWindowSample.hpp"

#include "logic/Controller.hpp"

void mainWindowInit(QApplication* app, Controller* controller)
{
  MainWindowSample* mainWindowSample = new MainWindowSample(controller);
  QObject::connect (mainWindowSample->getQuitGameButton(), SIGNAL(clicked()), app, SLOT(quit()));
  mainWindowSample->show();
}

int main(int argc, char* argv[])
{
  std::srand (unsigned(std::time(0)));

  Model model;
  Controller controller {&model};

  QApplication app(argc, argv);
  mainWindowInit(&app, &controller);

  return app.exec();
};
