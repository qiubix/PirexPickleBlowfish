#ifndef BOARDSAMPLE_HPP
#define BOARDSAMPLE_HPP

#include <QWidget>
#include "ui_BoardSample.h"

namespace Ui {
class BoardSample;
}

class BoardSample : public QWidget
{
    Q_OBJECT

public:
    explicit BoardSample(QWidget *parent = 0);
    ~BoardSample();

private:
    Ui::BoardSample *ui;
};

#endif // BOARDSAMPLE_HPP
