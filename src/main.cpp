#include <QtWidgets>
#include <QObject>
#include <iostream>
#include "logic/Dollar.hpp"
#include "gui/MainWindowSample.hpp"
#include "Logger.hpp"
#include <boost/log/trivial.hpp>

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

  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

  QApplication app(argc, argv);
  mainWindowInit(&app);
  dollarInit();
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}
