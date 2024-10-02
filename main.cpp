#include <QCoreApplication>
#include <QDebug>
#include <QDate>
#include <QMap>

#include "menureader.h"
#include "telegrammanager.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTextStream s(stdin);

	qInfo() << "Please insert first monday of the month (format: YYYY-MM-DD): ";
	QString mondayStr = s.readLine();
	QDate monday = QDate::fromString(mondayStr, Qt::ISODate);

	qInfo() << "Please insert the number of dishes: ";
	int numDishes = QString(s.readLine()).toInt();

	MenuReader menu("menu.xlsx", monday, numDishes);
	if (!menu.readFile())
	{
		qWarning() << "menu.xlsx file not found";
		return -1;
	}
	QMap<QDate, Menu> menus = menu.getAllMenus();

	TelegramManager tm(menus);
	tm.loop();
}
