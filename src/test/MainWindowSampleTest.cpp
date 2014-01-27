#include <QtGui>
#include <QtTest/QtTest>

#include "gui/MainWindowSample.hpp"
#include "logic/Board.hpp"

class MainWindowSampleTest : public QObject
{
  Q_OBJECT

private slots:
  void testLineEdit();
  void testNewGameButtonClick();
};

void MainWindowSampleTest::testLineEdit()
{
  MainWindowSample mainWindowSample(new Board);
  QLineEdit* lineEdit = mainWindowSample.getLineEdit();

  QTest::keyClicks(lineEdit, "hello world");
  QCOMPARE(lineEdit->text(), QString("hello world"));
}

void MainWindowSampleTest::testNewGameButtonClick()
{
  MainWindowSample mainWindowSample(new Board);
  QPushButton* newGameButton = mainWindowSample.getNewGameButton();
  QTextBrowser* textBrowser = mainWindowSample.getTextBrowser();
  QTest::mouseClick(newGameButton, Qt::LeftButton);
  QCOMPARE(textBrowser->toPlainText(), QString("New Game button clicked"));
}

QTEST_MAIN(MainWindowSampleTest)
#include "MainWindowSampleTest.moc"
