#ifndef MENUDEFS_H
#define MENUDEFS_H

#include <QString>
struct Menu
{
	QString firstCourse;
	QString brothCourse;
	//
	QString mainCourseMeat;
	QString mainCourseFish;
	QString mainCourseVeg;
	//
	QString sideDish;

	std::string toString() const {
			return (firstCourse + "\n"
				+ brothCourse + "\n"
				+ mainCourseMeat + "\n"
				+ mainCourseFish + "\n"
				+ mainCourseVeg + "\n"
				+ sideDish).toStdString();
		}

};

#endif // MENUDEFS_H
