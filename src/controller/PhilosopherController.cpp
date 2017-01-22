//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherController.h"
//////////////////////////////////

PhilosopherController::PhilosopherController(const std::string& name, QWidget* parent)
		: inherited(parent)
		, _ui(new Ui::PhilosopherView{})
		, _thread(name, this)
{
	_ui->setupUi(this);
	onUpdateUI();

	QObject::connect(&_thread, SIGNAL(updateUI()), this, SLOT(onUpdateUI()), Qt::QueuedConnection);
}

PhilosopherController::~PhilosopherController()
{
	_thread.stop();
}

void PhilosopherController::onKill()
{
	_thread.stop();
	delete this;//remove self
}

void PhilosopherController::showEvent(QShowEvent* event)
{
	inherited::showEvent(event);

	onUpdateUI();

	_thread.start();
}

void PhilosopherController::onUpdateUI()
{
	_ui->name->setText(_thread.getModel().getName().c_str());
	_ui->state->setText(_thread.getModel().getStateName().c_str());
}
