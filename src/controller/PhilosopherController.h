//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <QtWidgets/QWidget>
#include "PhilosopherMindController.h"

class PhilosopherController : public QWidget
{
Q_OBJECT
	using inherited = QWidget;
public:
	explicit PhilosopherController(const std::string& name, QWidget* parent = nullptr);

public slots:
	void onKill();

private:
	PhilosopherMindController _thread;
};


