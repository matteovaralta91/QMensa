#ifndef MENUDEFS_H
#define MENUDEFS_H

#include <QString>

static QString capitalizeFirst(QString str)
{
	if (str == "")
		return "";
    QString tmpStr = str.toLower();
    tmpStr[0] = tmpStr[0].toUpper();
    return tmpStr;
}

struct Menu
{
    QString firstColdCourse;
    QString firstCourse;
	QString brothCourse;
	//
	QString mainCourseMeat;
	QString mainCourseFish;
	QString mainCourseVeg;
	//
    QString sideDish;
    QString ethnicDish;

	std::string toString() const {
        QString tmpStr = (capitalizeFirst(firstColdCourse) + "\n"
                + capitalizeFirst(firstCourse) + "\n"
                + capitalizeFirst(brothCourse) + "\n"
                + capitalizeFirst(mainCourseMeat) + "\n"
                + capitalizeFirst(mainCourseFish) + "\n"
                + capitalizeFirst(mainCourseVeg) + "\n"
                + capitalizeFirst(sideDish) + "\n"
                + capitalizeFirst(ethnicDish));
            return tmpStr.toStdString();
		}

};

#endif // MENUDEFS_H
