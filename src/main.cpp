#include <QtWidgets>
#include <QObject>
#include <iostream>
#include <vector>
#include "gui/MainWindowSample.hpp"
#include "Logger.hpp"

#include "setup/TokenLoader.hpp"
#include "setup/GameBox.hpp"
#include "logic/Controller.hpp"

void mainWindowInit(QApplication* app, Board* modelBoard)
{
  MainWindowSample* mainWindowSample = new MainWindowSample(modelBoard);
  QObject::connect (mainWindowSample->getQuitGameButton(), SIGNAL(clicked()), app, SLOT(quit()));
  mainWindowSample->show();
}

int main(int argc, char* argv[])
{
  initLogging();

  Model* model = new Model;
  Controller* controller = new Controller(model);

  std::vector<std::string> armyFiles;
  armyFiles.push_back("../documentation/moloch.json");
  armyFiles.push_back("../documentation/outpost.json");
//  TokenLoader::getInstance() -> loadArmies(armyFiles, controller);

  QApplication app(argc, argv);
  mainWindowInit(&app, model -> getBoard());


  return app.exec();
}
