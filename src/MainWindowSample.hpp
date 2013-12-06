#ifndef MAINWINDOWSAMPLE_HPP
#define MAINWINDOWSAMPLE_HPP

#include <QWidget>

namespace Ui {
  class MainWindowSample;
}

class MainWindowSample : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindowSample(QWidget *parent = 0);
  ~MainWindowSample();

private:
  Ui::MainWindowSample *ui;
};

#endif // MAINWINDOWSAMPLE_HPP
