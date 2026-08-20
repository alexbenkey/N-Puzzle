/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadWorker.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 16:01:17 by othello           #+#    #+#             */
/*   Updated: 2026/08/20 20:26:08 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadWorker.hpp"
#include "Errors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

ThreadWorker::ThreadWorker(std::function<void()> f):
			function(std::move(f)),
			state(State::IDLE),
			thread(&ThreadWorker::run, this)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

ThreadWorker::~ThreadWorker(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DRED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
#endif

	this->setState(State::STOP);
	if (this->thread.joinable())
		this->thread.join();	
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	ThreadWorker::setState(State state)
{
	{
		std::lock_guard<std::mutex>	lock(this->internalMutex);
		this->state = state;
	}
	this->condition.notify_one();
}

ThreadWorker::State	ThreadWorker::getState(void) const
{
	std::lock_guard<std::mutex>	lock(this->internalMutex);
	return (this->state);
}

void	ThreadWorker::run(void)
{
	while (true)
	{
		std::unique_lock<std::mutex>	lock(this->internalMutex);
		switch (this->state)
		{
			case State::STOP:
				return ;
			case State::IDLE:
				this->condition.wait(lock, [this] { return (this->state != State::IDLE); });
				break;
			case State::RUNONCE:
				lock.unlock();	// allows this->function to change state
				this->function();
				if (this->getState() == State::RUNONCE)
					this->setState(State::IDLE);
				break;
			case State::RUNNING:
				lock.unlock(); // allows this->function 
				this->function();
				break;
			default:
				break;
		}
	}
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
