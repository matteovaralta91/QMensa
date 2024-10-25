#include "menureader.h"
#include <QDebug>

using namespace QXlsx;

MenuReader::MenuReader(QString xlsxName, QDate firstMonday, int numDishes)
	: xlsxName(xlsxName), firstMonday(firstMonday), numDishes(numDishes)
{
}

bool MenuReader::readFile()
{
	doc = std::make_unique<QXlsx::Document>(xlsxName);
	if (!doc->load())
	{
		return false;
	}

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

			if (cellStr == "SETTIMANA 1")
			{
				qInfo() << "Settimana 1 founded";
				menus.insert(getWeekMenu(firstMonday, rc, cc, 0));
			}
			else if (cellStr == "SETTIMANA 2")
			{
				qInfo() << "Settimana 2 founded";
				menus.insert(getWeekMenu(firstMonday, rc, cc, 1));
			}
			else if (cellStr == "SETTIMANA 3")
			{
				qInfo() << "Settimana 3 founded";
				menus.insert(getWeekMenu(firstMonday, rc, cc, 2));
			}
			else if (cellStr == "SETTIMANA 4")
			{
				qInfo() << "Settimana 4 founded";
				menus.insert(getWeekMenu(firstMonday, rc, cc, 3));
			}
		}
	}

	return true;
}

QMap<QDate, Menu> MenuReader::getAllMenus()
{
	return menus;
}

QMap<QDate, Menu> MenuReader::getDayMenu(QDate day, int row, int col)
{
	QMap<QDate, Menu> dayMenu;
	Menu menu;
	menu.firstColdCourse = doc->read(row + 0, col).toString();
	menu.firstCourse = doc->read(row + 1, col).toString();
	menu.brothCourse = doc->read(row + 2, col).toString();
	menu.mainCourseMeat = doc->read(row + 3, col).toString();
	menu.mainCourseFish = doc->read(row + 4, col).toString();
	menu.mainCourseVeg = doc->read(row + 5, col).toString();
	menu.sideDish = doc->read(row + 6, col).toString();
	menu.ethnicDish = doc->read(row + 7, col).toString();

	dayMenu.insert(day, menu);

	return dayMenu;
}

QMap<QDate, Menu> MenuReader::getWeekMenu(QDate day, int row, int col, int week)
{
	QMap<QDate, Menu> weekMenu;
	weekMenu.insert(getDayMenu(firstMonday.addDays(0 + 7 * week), row + 1 + 0 * numDishes, col));
	weekMenu.insert(getDayMenu(firstMonday.addDays(1 + 7 * week), row + 1 + 1 * numDishes, col));
	weekMenu.insert(getDayMenu(firstMonday.addDays(2 + 7 * week), row + 1 + 2 * numDishes, col));
	weekMenu.insert(getDayMenu(firstMonday.addDays(3 + 7 * week), row + 1 + 3 * numDishes, col));
	weekMenu.insert(getDayMenu(firstMonday.addDays(4 + 7 * week), row + 1 + 4 * numDishes, col));

	return weekMenu;
}
