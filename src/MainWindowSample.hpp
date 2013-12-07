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

private slots:
  void on_NewGameButton_clicked();

  void on_LoadGameButton_clicked();

  void on_QuitGameButton_clicked();

private:
  Ui::MainWindowSample *ui;
};

#endif // MAINWINDOWSAMPLE_HPP
