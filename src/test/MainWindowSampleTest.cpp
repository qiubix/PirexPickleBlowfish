#include <QtGui>
#include <QtTest/QtTest>

#include "MainWindowSample.hpp"

class MainWindowSampleTest : public QObject
{
  Q_OBJECT

private slots:
  void testNewGameButtonClick();
};

void MainWindowSampleTest::testNewGameButtonClick()
{
  MainWindowSample mainWindowSample;
  QLineEdit* lineEdit = mainWindowSample.getLineEdit();

  QTest::keyClicks(lineEdit, "hello world");
  QCOMPARE(lineEdit.text(), QString("hello wolrd"));
}

QTEST_MAIN(MainWindowSampleTest)
#include "mainwindowsample.moc"
