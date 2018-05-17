#ifndef NQQEXTENSION_H
#define NQQEXTENSION_H

#include <QObject>
#include <QUrl>

class QQmlApplicationEngine;
class MainWindow;

class NqqExtension : public QObject
{
	Q_OBJECT

public:
	NqqExtension(QString dirPath, MainWindow* ptr);

signals:
	void test();
	void buttonClick();

public slots:
	Q_INVOKABLE QString getTextEditContents() const;
	Q_INVOKABLE void setTextEditContents(QString str);

private:
	QQmlApplicationEngine* m_engine = nullptr;

	MainWindow* m_windowPtr;
};

#endif // NQQEXTENSION_H
