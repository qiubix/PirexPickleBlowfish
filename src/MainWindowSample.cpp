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

QPushButton* MainWindowSample::getNewGameButton()
{
  return ui->newGameButton;
}

QPushButton*MainWindowSample::getQuitGameButton()
{
  return ui->quitGameButton;
}

QTextBrowser* MainWindowSample::getTextBrowser()
{
  return ui->textBrowser;
}

MainWindowSample::~MainWindowSample()
{
  delete ui;
}

void MainWindowSample::on_newGameButton_clicked()
{
  ui->textBrowser->setText("New Game button clicked");
}

void MainWindowSample::on_loadGameButton_clicked()
{
  ui->textBrowser->setText("Load Game button clicked");
}

void MainWindowSample::on_quitGameButton_clicked()
{
  ui->textBrowser->setText("Quit Game button clicked");
}
