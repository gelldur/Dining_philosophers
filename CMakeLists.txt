CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(Dining_philosophers)

SET(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

SET(SOURCE_FILES
		src/main.cpp
		src/mainwindow.cpp src/mainwindow.h
		)

QT5_WRAP_UI(UIS_HDRS
		ui/mainwindow.ui
		)

ADD_EXECUTABLE(Dining_philosophers ${SOURCE_FILES} ${UIS_HDRS})

TARGET_INCLUDE_DIRECTORIES(Dining_philosophers PRIVATE
		src/
		${CMAKE_CURRENT_BINARY_DIR}
		./)

TARGET_LINK_LIBRARIES(Dining_philosophers Qt5::Core Qt5::Widgets Qt5::Gui)
