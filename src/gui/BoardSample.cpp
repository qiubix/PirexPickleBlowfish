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
