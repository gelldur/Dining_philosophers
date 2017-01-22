//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherMindController.h"
//////////////////////////////////

#include <iostream>
#include <QDebug>

PhilosopherMindController::PhilosopherMindController(const std::string& name, QObject* parent)
		: inherited(parent)
		, _model(name)
{
}

PhilosopherMindController::~PhilosopherMindController()
{
	//FIXME wait for threads etc
}

void PhilosopherMindController::run()
{
	while (isWorking())//eating forever
	{
		_forkPair.startUse();//acquire

		_model.changeState(Philosopher::State::EATING);
		std::cout << "Philospher " << _model.getName().c_str() << " is eating!" << std::endl;
		emit updateUI();

		//We will be eating for
		sleep(_eatingTime.count());
		_forkPair.stopUse();//release
		_model.changeState(Philosopher::State::THINKING);
		std::cout << "Philospher " << _model.getName().c_str() << " stops eating!" << std::endl;

		emit updateUI();
		sleep(_restTime.count());
	}
}

void PhilosopherMindController::stop()
{
	std::cout << "Philospher " << _model.getName().c_str() << " is stopping!" << std::endl;
	setWorking(false);
	yieldCurrentThread();
}

const Philosopher& PhilosopherMindController::getModel() const
{
	return _model;
}

void PhilosopherMindController::setWorking(bool isWorking)
{
	QMutexLocker locker(&_mutex);
	_working = isWorking;
}

bool PhilosopherMindController::isWorking()
{
	QMutexLocker locker(&_mutex);
	return _working;
}
