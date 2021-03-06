CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(Dining_philosophers)

SET(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

SET(SOURCE_FILES
		src/controller/PhilosopherController.cpp src/controller/PhilosopherController.h
		src/controller/PhilosopherMindController.cpp src/controller/PhilosopherMindController.h
		src/layout/FlowLayout.cpp src/layout/FlowLayout.h
		src/main.cpp
		src/MainWindow.cpp src/MainWindow.h
		src/model/ForkPair.cpp src/model/ForkPair.h
		src/model/Philosopher.cpp src/model/Philosopher.h
		)

QT5_WRAP_UI(UI
		ui/MainWindow.ui
		ui/philosopherView.ui
		)
QT5_ADD_RESOURCES(RESOURCES
		res/res.qrc
		)

ADD_EXECUTABLE(Dining_philosophers
		${SOURCE_FILES}
		${UI}
		${RESOURCES}
		)

TARGET_INCLUDE_DIRECTORIES(Dining_philosophers PRIVATE
		src/
		${CMAKE_CURRENT_BINARY_DIR}
		./)

TARGET_LINK_LIBRARIES(Dining_philosophers Qt5::Core Qt5::Widgets Qt5::Gui)
