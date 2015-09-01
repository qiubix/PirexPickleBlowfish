#include "MainWindowSample.hpp"
#include "ui_MainWindowSample.h"

#include "Board.hpp"
#include "ViewController.hpp"

MainWindowSample::MainWindowSample(Controller* modelController, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWindowSample)
{
  ui->setupUi(this);

  ViewController* controller = new ViewController(modelController, this);

  QGraphicsScene * scene = new QGraphicsScene(this);
  scene->setBackgroundBrush(Qt::darkGray);

  Field * middleField = modelController->getModelBoard()->getMiddleField();

  gui::Board * board = new gui::Board(controller, middleField);
  board -> setPos(0, 0);
  scene -> addItem(board);

  ui->graphicsView->setScene(scene);
  ui->graphicsView->show();
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
  ui->textBrowser->append("New Game button clicked");
}

void MainWindowSample::on_loadGameButton_clicked()
{
  ui->textBrowser->setText("Load Game button clicked");
}

void MainWindowSample::on_quitGameButton_clicked()
{
  ui->textBrowser->setText("Quit Game button clicked");
}
