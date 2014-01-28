#ifndef MAINWINDOWSAMPLE_HPP
#define MAINWINDOWSAMPLE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include "logic/Board.hpp"
#include "logic/Controller.hpp"

namespace Ui {
  class MainWindowSample;
}

class MainWindowSample : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindowSample(Controller* modelController, QWidget *parent = 0);
  QLineEdit* getLineEdit();
  QPushButton* getNewGameButton();
  QPushButton* getQuitGameButton();
  QTextBrowser* getTextBrowser();
  ~MainWindowSample();

private slots:
  void on_newGameButton_clicked();

  void on_loadGameButton_clicked();

  void on_quitGameButton_clicked();

private:
  Ui::MainWindowSample *ui;
};

#endif // MAINWINDOWSAMPLE_HPP
