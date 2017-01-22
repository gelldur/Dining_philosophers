//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "Philosopher.h"
//////////////////////////////////

Philosopher::Philosopher(const std::string& name)
		: _name(name)
{
}

Philosopher::State Philosopher::getState() const
{
	return _state;
}

const std::string& Philosopher::getName() const
{
	return _name;
}

bool Philosopher::changeState(Philosopher::State state)
{
	//TODO implement
	return false;
}
