//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <list>
#include <mutex>

class ForkPair
{
public:
	ForkPair();
	~ForkPair();

	void startUse();
	void stopUse();

private:
	static std::list<std::mutex> _forks;
	std::list<std::mutex>::iterator _myFork;
	std::pair<std::list<std::mutex>::iterator, std::list<std::mutex>::iterator> _myCurrentForks;

	std::pair<std::list<std::mutex>::iterator, std::list<std::mutex>::iterator> getForks() const;
};


