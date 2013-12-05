#ifndef BOARDSAMPLE_HPP
#define BOARDSAMPLE_HPP

#include "ui_BoardSample.h"
#include <QWidget>

namespace Ui {
  class BoardSample;
}

class BoardSample : public QWidget
{
  Q_OBJECT

public:
  explicit BoardSample(QWidget *parent = 0);
  ~BoardSample();

private slots:
  void on_newGameButton_clicked();

  void on_quitButton_clicked();

private:
  Ui::BoardSample *ui;
};

#endif // BOARDSAMPLE_HPP
