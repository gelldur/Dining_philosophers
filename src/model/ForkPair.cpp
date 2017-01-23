//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#include "ForkPair.h"
//////////////////////////////////

#include <iostream>
#include <cassert>
#include <algorithm>

std::list<ForkPair::Fork> ForkPair::_forks;
std::mutex ForkPair::_forksLock;

ForkPair::ForkPair(const std::string& owner)
		: _myCurrentForks{_forks.end(), _forks.end()}
{
	//ForkPair is created on main thread
	std::lock_guard<std::mutex> guard{_forksLock};

	_forks.emplace_back();//We can add fork even if some of forks are used currently
	_myFork = std::prev(_forks.end());//In list it is safe to store iterator
	_myFork->owner = owner;//For debug
	_myFork->isUsed = false;
	_myFork->isInvalid = false;

	for (auto& fork : _forks)
	{
		fork.isReady = false;
	}
}

ForkPair::~ForkPair()
{
	std::lock_guard<std::mutex> guard{_forksLock};

	_forks.erase(_myFork);//It should be safe to remove it because no one shouldn't acquire it
}

bool ForkPair::startUse()
{
	//Called in background thread
	if (_forks.size() < 2)
	{
		//not enough forks!
		return false;
	}

	bool anyReady = isAnyReady();
	if (anyReady == false && isAnyUsed())
	{
		return false;
	}

	_myCurrentForks = getForks();
	if (_myCurrentForks.first->isInvalid || _myCurrentForks.second->isInvalid)
	{
		return false;
	}

	if (anyReady == false && _myCurrentForks.first == _forks.begin())
	{
		//Only once executed when rearrange
		std::lock_guard<std::mutex> guard{_forksLock};
		_myCurrentForks.first->isReady = true;//make ready first one
		for (auto& fork : _forks)
		{
			//It means no one is using fork and we can unlock previous waiting philosophers
			//because we must rearrange them
			fork.mutex.unlock();
		}
	}

	if (_myCurrentForks.first->isReady)
	{
		//Enable one by one
		_myCurrentForks.first->isReady = true;
		_myCurrentForks.second->isReady = true;
	}
	else
	{
		return false;
	}

	_myCurrentForks.first->mutex.lock();
	//We have locked first fork
	if (_myCurrentForks.first->isInvalid)//is invalid fork so we should don't use it
	{
		_myCurrentForks.first->mutex.unlock();
		return false;
	}

	_myCurrentForks.second->mutex.lock();
	//We have locked first fork
	if (_myCurrentForks.second->isInvalid)//is invalid fork so we should don't use it
	{

		_myCurrentForks.first->mutex.unlock();//We previously locked it also so maybe order will change
		_myCurrentForks.second->mutex.unlock();//We unlock because it is not invalid
		return false;
	}

	_myCurrentForks.first->isUsed = true;//mar as used, for waiting and tracking
	_myCurrentForks.second->isUsed = true;

	return true;
}

void ForkPair::stopUse()
{
	//Called in background thread
	if (_myCurrentForks.first != _forks.end())
	{
		_myCurrentForks.second->mutex.unlock();
		_myCurrentForks.first->mutex.unlock();
	}
	_myCurrentForks.first->isUsed = false;
	_myCurrentForks.second->isUsed = false;
}

std::pair<std::list<ForkPair::Fork>::iterator, std::list<ForkPair::Fork>::iterator> ForkPair::getForks() const
{
	//Called in background thread
	auto myLeftFork = _myFork;
	auto myRightFork = std::next(myLeftFork);
	if (myRightFork == _forks.end())//make cyclic
	{
		myRightFork = _forks.begin();
	}

	if (std::distance(_forks.begin(), myLeftFork) > std::distance(_forks.begin(), myRightFork))
	{
		//Order forks by index to prevent deadlock
		return {myRightFork, myLeftFork};
	}
	return {myLeftFork, myRightFork};
}

void ForkPair::willBeRemoved()
{
	_myFork->isInvalid = true;
	rearrange();
}

bool ForkPair::shouldWeFinish() const
{
	//Called in background thread
	return !_myFork->isReady;
}

void ForkPair::rearrange()
{
	std::lock_guard<std::mutex> guard{_forksLock};
	for (auto& fork : _forks)
	{
		fork.isReady = false;
	}
}

bool ForkPair::isAnyUsed()
{
	std::lock_guard<std::mutex> guard{_forksLock};
	for (auto& fork : _forks)
	{
		if (fork.isUsed)
		{
			return true;
		}
	}
	return false;
}

bool ForkPair::isAnyReady()
{
	std::lock_guard<std::mutex> guard{_forksLock};
	for (auto& fork : _forks)
	{
		if (fork.isReady)
		{
			return true;
		}
	}
	return false;
}
