//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <chrono>

#include <QtCore/QThread>

#include <model/Philosopher.h>
#include <model/ForkPair.h>
#include <QtCore/QMutex>

class PhilosopherMindController : public QThread
{
Q_OBJECT
	using inherited = QThread;
public:
	PhilosopherMindController(const std::string& name, QObject* parent);
public slots:
	void stop();

	const Philosopher& getModel() const;

protected:
	void run() override;

private:
	std::chrono::seconds _eatingTime = std::chrono::seconds{5};
	Philosopher _model;
	ForkPair _forkPair;
	QMutex _mutex;
	bool _working = true;
};

