#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QMap>

#include "menureader.h"
#include "telegrammanager.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTextStream s(stdin);

	qInfo() << "Please insert the file name: ";
	QString filename = s.readLine();
	if (!QFile(filename).exists())
	{
		qInfo() << "File not exists";
		QCoreApplication::quit();
	}

	qInfo() << "Please insert first monday of the month (format: YYYY-MM-DD): ";
	QString mondayStr = s.readLine();
	QDate monday = QDate::fromString(mondayStr, Qt::ISODate);

	qInfo() << "Please insert the number of dishes: ";
	int numDishes = QString(s.readLine()).toInt();

	MenuReader menu(filename, monday, numDishes);
	if (!menu.readFile())
	{
		qWarning() << "menu file not correctly formatted";
		QCoreApplication::quit();
	}
	QMap<QDate, Menu> menus = menu.getAllMenus();

	QString lastFridayMenu = QString::fromStdString(menus.last().toString());
	lastFridayMenu.replace("\n", QString(QChar::CarriageReturn));

	qInfo() << "Check the last friday (" << menus.lastKey()
			<< ") menu: " << QChar::CarriageReturn
			<< lastFridayMenu;

	qInfo() << "Is that correct? (N/Y)";
	QString correct = s.readLine();

	if (correct.toUpper() == "Y")
	{
		qInfo() << "Starting telegram...";
		TelegramManager tm(menus);
		tm.loop();
	}
}
