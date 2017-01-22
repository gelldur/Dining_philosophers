#pragma once
#include <memory>

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = 0);

private:
	std::unique_ptr<Ui::MainWindow> _ui;
};
