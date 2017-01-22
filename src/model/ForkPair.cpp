//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "ForkPair.h"
//////////////////////////////////

#include <algorithm>

std::list<std::mutex> ForkPair::_forks;

ForkPair::ForkPair()
		: _myCurrentForks{_forks.end(), _forks.end()}
{
	//FIXME sync stuff
	_forks.emplace_back();
	_myFork = std::prev(_forks.end());//In list it is safe to store iterator
}

ForkPair::~ForkPair()
{
	stopUse();
	_forks.erase(_myFork);
}

void ForkPair::startUse()
{
	_myCurrentForks = getForks();

	_myCurrentForks.first->lock();
	_myCurrentForks.second->lock();
}

void ForkPair::stopUse()
{
	if (_myCurrentForks.first != _forks.end())
	{
		_myCurrentForks.first->unlock();
		_myCurrentForks.second->unlock();
	}
}

std::pair<std::list<std::mutex>::iterator, std::list<std::mutex>::iterator> ForkPair::getForks() const
{
	auto myLeftFork = _myFork;
	auto myRightFork = std::next(_myFork);
	if (myRightFork == _forks.end())
	{
		myRightFork = _forks.begin();
	}

	if (std::distance(_forks.begin(), myLeftFork) > std::distance(_forks.begin(), myRightFork))
	{
		return {myRightFork, myLeftFork};
	}
	return {myLeftFork, myRightFork};
}
