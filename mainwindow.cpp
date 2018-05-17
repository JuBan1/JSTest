#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QQmlContext>

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <qtimer.h>

#include "nqqextension.h"

#include <QJSEngine>

QJSEngine * eng;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/*
		the package.json of an extension contains some info regarding what to load.
		right now it'll contain the js file and its entry function as well as a list of
		all signals the extension wants to listen to.

		in this case it's only the "buttonClick" signal. the signals sit in the NqqExtension class for convenience
		but if this were to be used in Notepadqq we'd probably construct a couple interface classes and expose them to
		the extension instead. But for now NqqExt shows how to maintain a stable API for extensions even if we do all sorts
		of shenanigans under the hood.
	*/


	NqqExtension* ext = new NqqExtension(QFileInfo(qApp->arguments()[0]).canonicalPath(), this);

	connect(this, &MainWindow::onAction, ext, &NqqExtension::buttonClick);

	/*eng = new QJSEngine();
	eng->installExtensions(QJSEngine::ConsoleExtension);
	eng->globalObject().setProperty("myNumber", 123);

	auto k = eng->evaluate("console.log(myNumber++)");
	k.call();

	QJSValue fun = eng->evaluate("(function(a, b) { return a + b + myNumber++;})");
	QJSValueList args;
	args << 1 << 2;
	QJSValue threeAgain = fun.call(args);

	qDebug() << fun.call(args).toInt() << fun.call(args).toInt();


	QFile f("/home/s3rius/dev/qt/JSTest/test.js");
	f.open(QFile::ReadOnly);
	auto arr = f.readAll();

	QJSValue f2 = eng->evaluate(arr);

	qDebug() << eng->globalObject().hasProperty("foo");

	qDebug() << eng->globalObject().property("func").call().toString();*/
}

MainWindow::~MainWindow()
{
	delete ui;
}

QString MainWindow::getValue()
{
	return ui->textEdit->toPlainText();
}

void MainWindow::setValue(QString txt)
{
	ui->textEdit->setPlainText(txt);
}

void MainWindow::on_pushButton_clicked()
{
	emit onAction("button clicked");
}
