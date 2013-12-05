#include "BoardSample.hpp"

BoardSample::BoardSample(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardSample)
{
    ui->setupUi(this);
}

BoardSample::~BoardSample()
{
    delete ui;
}

void BoardSample::on_newGameButton_clicked()
{
  ui->label->setText("New board");
}

void BoardSample::on_quitButton_clicked()
{
  parentWidget()->close();
}
