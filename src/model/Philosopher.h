//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <string>

class Philosopher
{
public:
	Philosopher(const std::string& name);

	enum class State
	{
		EATING, THINKING
	};

	State getState() const;
	const std::string& getName() const;

	/**
	 * @param state we want move to
	 * @return true if state change is successful, false otherwise
	 */
	bool changeState(State state);

private:
	State _state = State::THINKING;
	std::string _name;
};


