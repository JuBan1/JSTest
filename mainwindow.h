#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlApplicationEngine>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	QString getValue();
	void setValue(QString);

private:
	Ui::MainWindow *ui;
	QQmlApplicationEngine* m_engine;
};

#endif // MAINWINDOW_H
