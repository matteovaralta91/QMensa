#ifndef MENUREADER_H
#define MENUREADER_H

#include <QString>
#include <QDate>
#include <QMap>
#include "menudefs.h"
#include "QXlsx/header/xlsxdocument.h"

class MenuReader
{
public:
	MenuReader(QString xlsxName, QDate firstMonday);
	void readFile();
	QMap<QDate, Menu> getAllMenus();

private:
	QMap<QDate, Menu> getDayMenu(QDate day, int row, int col);
	QMap<QDate, Menu> getWeekMenu(QDate day, int row, int col, int week);

	QString xlsxName;
	QDate firstMonday;
	std::unique_ptr<QXlsx::Document> doc;

	QMap<QDate, Menu> menus;
};

#endif // MENUREADER_H
