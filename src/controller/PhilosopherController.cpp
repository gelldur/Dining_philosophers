//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherController.h"
//////////////////////////////////

#include <cassert>

PhilosopherController::PhilosopherController(const std::string& name, QWidget* parent)
		: inherited(parent)
		, _ui(new Ui::PhilosopherView{})
		, _thread(name, this)
{
	//PhilosopherController is created on main thread
	_ui->setupUi(this);
	onUpdateUI();

	QObject::connect(&_thread, SIGNAL(updateUI()), this, SLOT(onUpdateUI()), Qt::QueuedConnection);
	//When thread will finish we will delete ourselves
	QObject::connect(&_thread, SIGNAL(finished()), this, SLOT(deleteLater()), Qt::QueuedConnection);
}

PhilosopherController::~PhilosopherController()
{
	_thread.stop();
	_thread.quit();
	_thread.wait();//We want be sure
}

void PhilosopherController::onKill()
{
	//Will be called on main thread
	_thread.stop();
}

void PhilosopherController::showEvent(QShowEvent* event)
{
	inherited::showEvent(event);
	onUpdateUI();

	_thread.start();//We wan't run thread for all the time out philosopher lives
}

void PhilosopherController::onUpdateUI()
{
	_ui->name->setText(_thread.getModel().getName().c_str());
	_ui->state->setText(_thread.getModel().getStateName().c_str());
	if (_thread.getModel().getState() == Philosopher::State::EATING)
	{
		QPalette palette = _ui->state->palette();
		palette.setColor(_ui->state->backgroundRole(), Qt::yellow);
		_ui->state->setPalette(palette);
		_ui->state->setAutoFillBackground(true);
	}
	else
	{
		_ui->state->setAutoFillBackground(false);
	}
}
