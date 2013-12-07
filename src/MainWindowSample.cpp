#include "MainWindowSample.hpp"
#include "ui_MainWindowSample.h"

MainWindowSample::MainWindowSample(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWindowSample)
{
  ui->setupUi(this);
}

QLineEdit* MainWindowSample::getLineEdit()
{
  return ui->lineEdit;
}

MainWindowSample::~MainWindowSample()
{
  delete ui;
}

void MainWindowSample::on_NewGameButton_clicked()
{
  ui->textBrowser->setText("New Game button clicked");
}

void MainWindowSample::on_LoadGameButton_clicked()
{
  ui->textBrowser->setText("Load Game button clicked");
}

void MainWindowSample::on_QuitGameButton_clicked()
{
  ui->textBrowser->setText("Quit Game button clicked");
}
