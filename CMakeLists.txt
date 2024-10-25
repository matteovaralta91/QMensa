cmake_minimum_required(VERSION 3.14)

project(QMensa LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Td 1.8.38 REQUIRED PATHS ./tdlib)

add_subdirectory(QXlsx)

add_executable(QMensa
	main.cpp
	menudefs.h
	menureader.h menureader.cpp
	telegrammanager.h telegrammanager.cpp
)
target_link_libraries(QMensa Qt${QT_VERSION_MAJOR}::Core QXlsx::QXlsx Td::TdStatic)

install(TARGETS QMensa
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
