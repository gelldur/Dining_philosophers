//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherMindController.h"
//////////////////////////////////

#include <QDebug>

PhilosopherMindController::PhilosopherMindController(const std::string& name, QObject* parent)
		: inherited(parent)
		, _model(name)
{
}

void PhilosopherMindController::run()
{
	inherited::run();

	bool isWorking = true;
	while (isWorking)//eating forever
	{
		_forkPair.startUse();//acquire
		//TODO update GUI
		qDebug() << "Philospher " << _model.getName().c_str() << " is eating!";
		{
			QMutexLocker locker(&_mutex);
			isWorking = _working;
		}

		//We will be eating for
		sleep(_eatingTime.count());
		_forkPair.stopUse();//release
		//TODO update GUI

		{
			QMutexLocker locker(&_mutex);
			isWorking = _working;
		}
	}
}

void PhilosopherMindController::stop()
{
	qDebug() << "Philospher " << _model.getName().c_str() << " is stopping!";
	QMutexLocker locker(&_mutex);
	_working = false;
}

const Philosopher& PhilosopherMindController::getModel() const
{
	return _model;
}

