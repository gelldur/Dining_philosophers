//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <list>
#include <mutex>
#include <atomic>

class ForkPair
{
public:
	ForkPair(const std::string& owner);
	~ForkPair();

	/**
	 * @return true if we successfully obtain forks, false otherwise
	 */
	bool startUse();

	/**
	 * Do nothing if we do not acquire forks
	 */
	void stopUse();

	/**
	 * If we don't acquire forks it will return false
	 * @return true if someone want to quit, false otherwise
	 */
	bool shouldWeFinish() const;

	void willBeRemoved();

private:
	static std::mutex _forksLock;//Simple lock for all forks. Used when someone sits down or want to go
	struct Fork
	{
		std::string owner;
		std::mutex mutex;
		std::atomic<bool> isReady;
		std::atomic<bool> isUsed;
		std::atomic<bool> isInvalid;
	};
	static std::list<Fork> _forks;
	std::list<Fork>::iterator _myFork;
	std::pair<std::list<Fork>::iterator, std::list<Fork>::iterator> _myCurrentForks;

	std::pair<std::list<Fork>::iterator, std::list<Fork>::iterator> getForks() const;
	void rearrange();
	static bool isAnyUsed();
	static bool isAnyReady();
};


