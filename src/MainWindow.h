#pragma once
#include <memory>

#include <QMainWindow>

#include <ui_MainWindow.h>

#include <model/ForkPair.h>
#include <QtWidgets/QScrollArea>
#include <controller/PhilosopherController.h>

class MainWindow : public QMainWindow
{
Q_OBJECT
	using inherited = QMainWindow;
public:
	explicit MainWindow(QWidget* parent = nullptr);

public slots:
	void onStart();
	void onAddPhilisopher();
	void onRemovePhilosopher();

private:
	std::unique_ptr<Ui::MainWindow> _ui;

	/**
	 * @return layout with philosphers
	 */
	QScrollArea* getTable();
	void goToTable();
};
