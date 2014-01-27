#ifndef VIEWCONTROLLER_HPP
#define VIEWCONTROLLER_HPP

#include <QObject>

#include "logic/Field.hpp"

class ViewController : public QObject
{
  Q_OBJECT

public:
  ViewController(QObject *parent = 0);

public slots:
  void fieldClicked(Field* field);
  void handFieldClicked(int player, int whichToken);

};

#endif // VIEWCONTROLLER_HPP
