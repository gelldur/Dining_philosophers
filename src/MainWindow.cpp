#include "MainWindow.h"

#include <cassert>
#include <cmath>

#include <layout/FlowLayout.h>

MainWindow::MainWindow(QWidget* parent)
		: inherited(parent)
		, _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);
	getTable()->setLayout(new FlowLayout());
	//TODO automatic start in: X s
}

void MainWindow::onStart()
{
	auto philosophersCount = _ui->spinBox->value();

	for (int i = 0; i < philosophersCount; ++i)
	{
		onAddPhilisopher();
	}
	goToTable();
}

void MainWindow::onAddPhilisopher()
{
	static int number = 0;//integer for name generation

	auto tableGrid = getTable();
	//Executed on main thread
	tableGrid->layout()->addWidget(new PhilosopherController("Foo-" + std::to_string(++number)));
}

void MainWindow::onRemovePhilosopher()
{
	auto tableGrid = getTable();
	if (tableGrid->layout()->count() < 1)
	{
		return;
	}
	//Remove last one
	auto philosopher = dynamic_cast<PhilosopherController*>(tableGrid->layout()
			->takeAt(tableGrid->layout()->count() - 1)->widget());
	philosopher->onKill();
}

QScrollArea* MainWindow::getTable()
{
	assert(_ui->stackedWidget->count() > 1);
	auto tableGrid = _ui->stackedWidget->widget(1)->findChild<QScrollArea*>("table");
	assert(tableGrid);
	return tableGrid;
}

void MainWindow::goToTable()
{
	assert(_ui->stackedWidget->count() > 1);
	_ui->stackedWidget->setCurrentIndex(1);
}

