#include <QtWidgets>
#include <QObject>
#include <QString>
#include <QDebug>
#include <iostream>
#include <vector>
#include <ctime>
#include "gui/MainWindowSample.hpp"

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

  Model* model = new Model;
  Controller* controller = new Controller(model);

  std::vector<std::string> armyFiles;
  armyFiles.push_back("moloch.json");
  armyFiles.push_back("outpost.json");
  TokenLoader::getInstance() -> loadArmies(armyFiles, controller);
  controller -> initializeNewPlayer(MOLOCH);
  controller -> initializeNewPlayer(OUTPOST);

  QApplication app(argc, argv);
  mainWindowInit(&app, controller);

  std::vector<Token*> tokens = model -> getCurrentPlayer() -> hiddenTokens;
  for (unsigned i=0; i<tokens.size(); ++i) {
    qDebug() << tokens.at(i) -> getName().c_str();
  }

  return app.exec();
}
