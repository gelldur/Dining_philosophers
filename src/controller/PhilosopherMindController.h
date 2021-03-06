//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <chrono>
#include <memory>

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
	virtual ~PhilosopherMindController();

	/**
	 * Stops thread from working.
	 * It is safe to call it multiple times
	 */
	void stop();

public slots:
	const Philosopher& getModel() const;

signals:
	void updateUI();

protected:
	void run() override;

private:
	std::chrono::seconds _eatingTime = std::chrono::seconds{3};

	ForkPair _forkPair;

	Philosopher _model;
	QMutex _mutex;
	bool _working = true;

	void setWorking(bool isWorking);
	bool isWorking();
};


