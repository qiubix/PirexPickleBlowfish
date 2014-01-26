#ifndef VIEWCONTROLLER_HPP
#define VIEWCONTROLLER_HPP

#include <QObject>

class ViewController : public QObject
{
  Q_OBJECT

public:
  ViewController(QObject *parent = 0);

public slots:
  void fieldClicked(void);
  void handFieldClicked(void);

};

#endif // VIEWCONTROLLER_HPP
