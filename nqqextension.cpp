#include "nqqextension.h"

#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include "mainwindow.h"
#include <QApplication>


NqqExtension::NqqExtension(QString dirPath, MainWindow* ptr)
{
	m_windowPtr = ptr;

	qDebug() << "Trying to find an extension in " << dirPath;

	// Read JSON file
	QFile file(dirPath + "/package.json");
	file.open(QIODevice::ReadOnly);

	if(!file.isOpen())
		return;

	QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
	QJsonObject json = doc.object();

	QString entryFile = json["entryfile"].toString();
	QString entryPoint = json["entrypoint"].toString();

	if(entryFile.isEmpty() || entryPoint.isEmpty())
		return;


	QString sigs;
	QJsonObject sigObj = json["signals"].toObject();
	for(auto it = sigObj.begin(); it != sigObj.end(); it++) {
		QString key = it.key();

		key[0] = key[0].toUpper();
		key = "on" + key;

		sigs += key + ": Main." + it.value().toString() + "()\n";
	}

	m_engine = new QQmlApplicationEngine(this);
	m_engine->rootContext()->setContextProperty("NqqExt", this);

	/*
	 * This is where some good ol' misuse is happening. QML is designed for GUI
	 * but instead of actually creating graphical items here (which wouldn't do much anyways
	 * since there's no window to show them in) I'm just creating a 'Connections'-object to
	 * tie C++ and QML together and use the QQmlEngine to host our extension.

	*/
	QString qml =
			"import QtQml 2.2\n"
			"import '%1' as Main\n"
			"Connections {\n"
			"id: root\n"
			"target: NqqExt\n"
			"Component.onCompleted: Main.%2()\n"
			"%3"
			"}";


	qml = qml.arg(entryFile).arg(entryPoint).arg(sigs);

	// Uncomment to see how the final QML file would look like
	//qDebug() << qml;

	m_engine->loadData(qml.toLatin1(), QUrl::fromLocalFile(dirPath + "/"));

	/*if(m_engine->rootObjects().isEmpty())
		return;

	auto obj = m_engine->rootObjects().first();

	if(!obj)
		return;

	QVariant returnedValue;
	QVariant msg = "Hello from C++";
	QMetaObject::invokeMethod(obj, "myQmlFunction",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, msg));*/
}

QString NqqExtension::getTextEditContents() const
{
	return m_windowPtr->getValue();
}

void NqqExtension::setTextEditContents(QString str)
{
	m_windowPtr->setValue(str);
}
