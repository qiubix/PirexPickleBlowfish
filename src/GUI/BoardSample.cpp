#include "BoardSample.hpp"
#include "ui_BoardSample.h"

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
