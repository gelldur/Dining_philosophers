//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherMindController.h"
//////////////////////////////////

#include <iostream>
#include <QDebug>

PhilosopherMindController::PhilosopherMindController(const std::string& name, QObject* parent)
		: inherited(parent)
		, _forkPair(name)
		, _model(name)
{
	//PhilosopherMindController is created on main thread
}

PhilosopherMindController::~PhilosopherMindController()
{
	//In dtor we will relase our fork
	//Fork should bo not accessible by other until full remove
	std::cout << "Philospher " << _model.getName().c_str() << " dies" << std::endl;
}

void PhilosopherMindController::run()
{
	while (isWorking())//eating until we don't stand up
	{
		std::cout << "Philospher " << _model.getName().c_str() << " want to eat" << std::endl;
		if (_forkPair.startUse() == false)//acquire
		{
			std::cout << "Philospher " << _model.getName().c_str() << " can't eat" << std::endl;
			msleep(16);
			continue;
		}
		_model.changeState(Philosopher::State::EATING);
		std::cout << "Philospher " << _model.getName().c_str() << " is eating!" << std::endl;
		emit updateUI();

		//We will be eating for
		std::chrono::milliseconds eatingTime = _eatingTime;
		while (eatingTime.count() > 0 && isWorking())
		{
			std::chrono::milliseconds delay{100};
			msleep(delay.count());
			eatingTime -= delay;

			//Check forks. Maybe someone would like to stand up and go away with his fork :)
			if (_forkPair.shouldWeFinish())
			{
				//someone would like to go away. So we stop eating! Or maybe someone new want to sit.
				//It is rude to eat when someone wan't to sit. Simply wait for him :)
				break;
			}
		}
		_forkPair.stopUse();//release
		_model.changeState(Philosopher::State::THINKING);
		std::cout << "Philospher " << _model.getName().c_str() << " stops eating!" << std::endl;

		emit updateUI();
	}
	std::cout << "Philospher " << _model.getName().c_str() << " stops working!" << std::endl;
	emit updateUI();
}

void PhilosopherMindController::stop()
{
	std::cout << "Philospher " << _model.getName().c_str() << " is stopping!" << std::endl;
	setWorking(false);

	//Mark our fork that we want stand up and go away from table. So no one can use our fork untill we will remove
	_forkPair.willBeRemoved();
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
