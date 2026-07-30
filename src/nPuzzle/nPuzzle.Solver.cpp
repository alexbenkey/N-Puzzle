/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:52:09 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/30 11:13:41 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Solver.hpp"
#include "nPuzzle.State.hpp"
#include "nPuzzle.Target.hpp"

#include "colors.hpp"
#include "heuristic.hpp"
#include "Errors.hpp"

#include <iostream>	// std::stream
#include <algorithm>	// std::sort

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::Solver::Solver(nPuzzle& puzzle):
	puzzle(puzzle)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->heuristic = 1;
	this->queueIndex = -1;
}

// nPuzzle::Solver::Solver(const Solver &src)
// {
// #if DEBUG >= DEBUG_TRACE
// 	std::cout	<< C_DGREEN	<< "Copy constructor "
// 				<< C_GREEN	<< __func__
// 				<< C_DGREEN	<< " called."
// 				<< C_RESET	<< std::endl;
// #endif
// 	*this = src;
// }

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzle::Solver::~Solver(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DRED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;	
	this->clearQueue();
	this->clearVisited();
#endif
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

bool	nPuzzle::Solver::solve(void)
{
TRACE_POSITION();
	while (!this->isSolved())
		this->solveStep(false);
	return (this->isSolved());
}

bool	nPuzzle::Solver::solveStep(bool calculateAllHeuristics)
{
TRACE_POSITION();
	// Prevent solving of already solved puzzle
	if (this->isSolved())
		return (true);
	// Prevent Solving of unsolvable puzzle

	// Create first queue item for starting position
	if (this->queue.size() == 0)
		this->processState(new nPuzzle::State(*this->puzzle.state), calculateAllHeuristics);
	// Retrieve first element from queue
	nPuzzle::State*	current = this->popQueue();
	this->visited.push_back(current);
	// Create upto 4 new states, one per direction and process them
	for (nPuzzle::Direction direction : {
		nPuzzle::Direction::UP,
		nPuzzle::Direction::RIGHT,
		nPuzzle::Direction::DOWN,
		nPuzzle::Direction::LEFT,
	})
	{
		nPuzzle::State*	next = new nPuzzle::State(*current);
		if (next->move(direction))
			this->processState(next, calculateAllHeuristics);
		else
			delete next;
	}
	// maintain valid queueIndex
	this->maintainValidQueueIndex();
// #if DEBUG >= DEBUG_DEBUG
// 	// print queue
// 	this->printQueueStatus();
// #endif
	return (isSolved());
}

void	nPuzzle::Solver::processState(nPuzzle::State* state, bool calculateAllHeuristics)
{
TRACE_POSITION();
	// Configure state for heuristics
	if (!state->setUsedHeuristic(this->heuristic))
	{
		delete state;
		return ;
	}
	// Validate state is new
	if (this->stateHasAlreadyBeenVisited(state) ||\
		this->stateIsAlreadyInQueue(state))
		return ;
	// Calculate heuristics
	const nPuzzle::Board&	target = this->puzzle.getTarget().getBoard();
	if (calculateAllHeuristics)
		state->calculateHeuristic(target);
	else
		state->calculateHeuristic(this->heuristic, target);
	// Store state in Queue
	this->addToQueue(state);
TRACE_POSITION();
}

bool	nPuzzle::Solver::stateHasAlreadyBeenVisited(nPuzzle::State* state)
{
	std::vector<nPuzzle::State*>::iterator	foundItem;

	foundItem = std::find_if(
		this->visited.begin(), 
		this->visited.end(), 
		[state] (const nPuzzle::State* candidate){return candidate->sameBoard(*state);});
	if (foundItem == this->visited.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->visited.erase(foundItem);
		return (false);
	}
	return (true);
}

bool	nPuzzle::Solver::stateIsAlreadyInQueue(nPuzzle::State* state)
{
	std::vector<nPuzzle::State*>::iterator	foundItem;

	foundItem = std::find_if(this->queue.begin(), this->queue.end(), [state] (const nPuzzle::State *candidate){ return candidate->sameBoard(*state); });
	if (foundItem == this->queue.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->queue.erase(foundItem);
		return (false);
	}
	return (true);
}

void	nPuzzle::Solver::addToQueue(nPuzzle::State* state)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	this->queue.push_back(state);
	std::sort(
		this->queue.begin(),
		this->queue.end(), 
		[](const nPuzzle::State* lhs, const nPuzzle::State *rhs) { return *lhs < *rhs; }
	);
}

nPuzzle::State*	nPuzzle::Solver::popQueue(void)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	if (this->queue.size() == 0)
		return (nullptr);
	nPuzzle::State* state = this->queue.front();
	this->queue.erase(this->queue.begin());
	return (state);
}

size_t	nPuzzle::Solver::getQueueSize(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	return (this->queue.size());
}

void	nPuzzle::Solver::incrementQueueIndex(void)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	++this->queueIndex;
	this->maintainValidQueueIndex();
}
void	nPuzzle::Solver::decrementQueueIndex(void)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	--this->queueIndex;
	this->maintainValidQueueIndex();
}
void	nPuzzle::Solver::maintainValidQueueIndex(void)
{
	size_t	size = this->queue.size();

	if (!size)
		this->queueIndex = -1;
	else if (this->queueIndex < 0)
		this->queueIndex = 0;
	else if (this->queueIndex >= size)
		this->queueIndex = size - 1;
}

int32_t	nPuzzle::Solver::getQueueIndex(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	return (this->queueIndex);
}

const nPuzzle::State&	nPuzzle::Solver::getQueueMember(int32_t i) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	if (this->queue.size())
		return (*this->queue.at(i));
	return (*this->puzzle.state);
}

int32_t	nPuzzle::Solver::getBestHeuristic(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	if (this->queue.size() == 0)
		return (this->puzzle.state->getHeuristic(this->heuristic));
	return (this->queue.at(0)->getHeuristic(this->heuristic));
}

bool	nPuzzle::Solver::isSolved(void) const
{
	return (this->getQueueSize() > 0 && this->queue[0]->getHeuristic(this->heuristic) == 0);
}

void	nPuzzle::Solver::getSolution(void) const
{
	// std::lock_guard<std::mutex>	lock(this->queueMutex);
}

void	nPuzzle::Solver::printQueueStatus(void) const
{
	std::fprintf(stderr, "# Queue[%lu]\n", this->getQueueSize());
	for (const nPuzzle::State* state : this->queue)
		this->printQueueNodeStatus(state);
	if (this->isSolved())
	{
		std::fprintf(stderr, "#  Solved:\n");
		this->printQueueNodeStatus(this->queue.at(0));
	}
	std::fflush(stderr);
}

void	nPuzzle::Solver::printQueueNodeStatus(const nPuzzle::State* state) const
{
	int32_t	cost = state->getCost();
	int32_t	heuristic = state->getHeuristic(this->heuristic);
	std::fprintf(stderr, "#  %-16p g: %4i  h: %4i  f: %4i\n", state, cost, heuristic, cost + heuristic);
}

void	nPuzzle::Solver::clearQueue(void)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	for (nPuzzle::State* state : this->queue)
		delete state;
	this->queue.clear();
	this->queueIndex = -1;
}

void	nPuzzle::Solver::clearVisited(void)
{
	// std::lock_guard<std::mutex>	lock(this->queueMutex);
	for (nPuzzle::State* state : this->visited)
		delete state;
	this->visited.clear();
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
