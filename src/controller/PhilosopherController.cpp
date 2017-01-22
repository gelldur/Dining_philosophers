//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "PhilosopherController.h"
//////////////////////////////////

#include <ui_philosopherView.h>

PhilosopherController::PhilosopherController(const std::string& name, QWidget* parent)
		: inherited(parent)
		, _thread(name, this)
{
	Ui::PhilosopherView view;
	view.setupUi(this);

	view.name->setText(_thread.getModel().getName().c_str());
	view.state->setText(_thread.getModel().getStateName().c_str());
}

void PhilosopherController::onKill()
{
	delete this;//remove self
}
