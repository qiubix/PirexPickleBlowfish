#include <QtWidgets>
#include <QObject>
#include <iostream>
#include <vector>
#include "gui/MainWindowSample.hpp"
#include "Logger.hpp"

#include "setup/TokenLoader.hpp"
#include "setup/GameBox.hpp"
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
  initLogging();

  Model* model = new Model;
  Controller* controller = new Controller(model);

  std::vector<std::string> armyFiles;
  armyFiles.push_back("../documentation/moloch.json");
  armyFiles.push_back("../documentation/outpost.json");
//  TokenLoader::getInstance() -> loadArmies(armyFiles, controller);
//  controller -> initializeNewPlayer(MOLOCH);
//  controller -> initializeNewPlayer(OUTPOST);

  QApplication app(argc, argv);
  mainWindowInit(&app, controller);


  return app.exec();
}
