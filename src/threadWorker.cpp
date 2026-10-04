/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadWorker.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 16:01:17 by othello           #+#    #+#             */
/*   Updated: 2026/10/04 14:33:35 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadWorker.hpp"
#include "Errors.hpp"
#include "colors.hpp"

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
	this->condition.notify_all();
}

void	ThreadWorker::pauseAndWait(void)
{
	std::unique_lock<std::mutex>	lock(this->internalMutex);

	if (this->state != State::STOP)
		this->state = State::IDLE;
	while (this->active)
		this->condition.wait(lock);
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
				this->state = State::IDLE;
				this->active = true;
				lock.unlock(); // allows this->function to change state
				this->function();
				lock.lock();
				this->active = false;
				this->condition.notify_all();
				break;
				// Fall through: consume the request, then execute once.
			case State::RUNNING:
				this->active = true;
				lock.unlock(); // allows this->function to change state
				this->function();
				lock.lock();
				this->active = false;
				this->condition.notify_all();
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
