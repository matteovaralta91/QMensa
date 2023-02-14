#include "menureader.h"
#include <QDebug>

using namespace QXlsx;

MenuReader::MenuReader(QString xlsxName, QDate firstMonday)
	: xlsxName(xlsxName), firstMonday(firstMonday)
{
}

void MenuReader::readFile()
{
	doc = std::make_unique<QXlsx::Document>(xlsxName);
	if (!doc->load())
		return;

	int row = 1; int col = 1;
	QVariant var = doc->read( row, col );
	// check type of var for more information
	qDebug() << var.toString();

	// get full cells of current sheet
	int maxRow = -1;
	int maxCol = -1;
	Worksheet* wsheet = (Worksheet*) doc->currentWorksheet();
	wsheet->getFullCells( &maxRow, &maxCol );

	for (int rc = 1; rc <= maxRow; rc++)
	{
		for (int cc = 1; cc <= maxCol; cc++)
		{
			QString cellStr = doc->read( rc, cc ).toString();
			qDebug() << "( row : " << rc
					 << ", col : " << cc
					 << ") " << doc->read( rc, cc ); // display cell value

			if (cellStr == "SETTIMANA 1")
			{
				int week = 0;
				qInfo() << "Settimana 1 founded";
				menus.insert(getDayMenu(firstMonday.addDays(0 + 7 * week), rc, cc + 1));
				menus.insert(getDayMenu(firstMonday.addDays(1 + 7 * week), rc, cc + 2));
				menus.insert(getDayMenu(firstMonday.addDays(2 + 7 * week), rc, cc + 3));
				menus.insert(getDayMenu(firstMonday.addDays(3 + 7 * week), rc, cc + 4));
				menus.insert(getDayMenu(firstMonday.addDays(4 + 7 * week), rc, cc + 5));
			}
		}
	}
}

QMap<QDate, Menu> MenuReader::getAllMenus()
{
	return menus;
}

QMap<QDate, Menu> MenuReader::getDayMenu(QDate day, int row, int col)
{
	QMap<QDate, Menu> dayMenu;
	Menu menu;
	menu.firstCourse = doc->read(row + 1, col).toString();
	menu.brothCourse = doc->read(row + 2, col).toString();
	menu.mainCourseMeat = doc->read(row + 3, col).toString();
	menu.mainCourseFish = doc->read(row + 4, col).toString();
	menu.mainCourseVeg = doc->read(row + 5, col).toString();
	menu.sideDish = doc->read(row + 6, col).toString();

	dayMenu.insert(day, menu);

	return dayMenu;
}

QMap<QDate, Menu> MenuReader::getWeekMenu(QDate day, int row, int col, int week)
{
	QMap<QDate, Menu> weekMenu;
	return weekMenu;
}
