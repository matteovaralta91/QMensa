#include <QCoreApplication>
#include <QDebug>
#include <QDate>
#include <QMap>

#include "menureader.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qInfo() << "Please insert first monday of the month (format: YYYY-MM-DD): ";
	QTextStream s(stdin);
	QString mondayStr = s.readLine();
	QDate monday = QDate::fromString(mondayStr, Qt::ISODate);

	MenuReader menu("menu.xlsx", monday);
	menu.readFile();
	QMap<QDate, Menu> menus = menu.getAllMenus();
	return a.exec();
}
