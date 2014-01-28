#ifndef VIEWCONTROLLER_HPP
#define VIEWCONTROLLER_HPP

#include <QObject>

#include "logic/Field.hpp"
#include "logic/Controller.hpp"
#include "BoardField.hpp"
#include "SideField.hpp"

class ViewController : public QObject
{
  Q_OBJECT

public:
  ViewController(Controller* modelController, QObject *parent = 0);

public slots:
  void fieldClicked(BoardField* field);
  void handFieldClicked(SideField* field);

private:
  Controller* modelController;
};

#endif // VIEWCONTROLLER_HPP
