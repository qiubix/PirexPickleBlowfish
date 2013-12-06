#include "MainWindowSample.hpp"
#include "ui_MainWindowSample.h"

MainWindowSample::MainWindowSample(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWindowSample)
{
  ui->setupUi(this);
}

MainWindowSample::~MainWindowSample()
{
  delete ui;
}
