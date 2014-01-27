#ifndef VIEWCONTROLLER_HPP
#define VIEWCONTROLLER_HPP

#include <QObject>

#include "logic/Field.hpp"
#include "BoardField.hpp"
#include "SideField.hpp"

class ViewController : public QObject
{
  Q_OBJECT

public:
  ViewController(QObject *parent = 0);

public slots:
  void fieldClicked(BoardField* field);
  void handFieldClicked(SideField* field);

};

#endif // VIEWCONTROLLER_HPP
