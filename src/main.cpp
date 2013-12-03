#include <iostream>
#include "GUI/BoardSample.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  BoardSample boardSample;
  boardSample.show();
  std::cout << "Hello World!" << std::endl;
  return app.exec();
}

int firstFunction (int argument)
{
  if (argument > 0) {
    argument = 0;
  }
  else {
    argument = 1;
  }
  return argument;
}
