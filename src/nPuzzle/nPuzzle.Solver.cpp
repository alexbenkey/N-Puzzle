/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:52:09 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/10 20:04:31 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Solver.hpp"
#include "nPuzzle.State.hpp"
#include "nPuzzle.Target.hpp"
#include "nPuzzle.Board.hpp"
#include "nPuzzle.Board.Tile.hpp"

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
	puzzle(puzzle),
	heuristicIndex(puzzle.heuristicIndex)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->workerState = STOP;
	this->solved = false;
	this->solvability.store(nPuzzle::Solvability::UNKNOWN);
}

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
#endif
	this->stopWorker();
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

WorkerState	nPuzzle::Solver::getWorkerState(void) const
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	return (this->workerState);
}

void	nPuzzle::Solver::setWorkerState(WorkerState state)
{
	{
		std::lock_guard<std::mutex>	lock(this->mutex);
		this->workerState = state;
	}
	this->workerCondition.notify_one();
}

void	nPuzzle::Solver::ensureActiveWorker(void)
{
	if (this->worker.joinable())
		return ;
	this->setWorkerState(WorkerState::IDLE);
	this->worker = std::thread(&nPuzzle::Solver::solveWorker, this);
}

void	nPuzzle::Solver::stopWorker(void)
{
	this->setWorkerState(WorkerState::STOP);
	if (this->worker.joinable())
		this->worker.join();
}

void	nPuzzle::Solver::setCalculateAllHeuristics(bool all)
{
	std::unique_lock<std::mutex>	lock(this->mutex);

	this->calculateAllHeuristics = all;
}
bool	nPuzzle::Solver::getCalculateAllHeuristics(void) const
{
	std::unique_lock<std::mutex>	lock(this->mutex);

	return (this->calculateAllHeuristics);
}

void	nPuzzle::Solver::solveWorker(void)
{
	while (this->getWorkerState() > WorkerState::STOP)
	{
		std::unique_lock<std::mutex>	lock(this->mutex);
		this->workerCondition.wait(lock, [this]() { return this->workerState != WorkerState::IDLE; });
		lock.unlock();
		this->solveStepWorker();
		if (this->getWorkerState() == WorkerState::RUNONE)
			this->setWorkerState(WorkerState::IDLE);
	}
}

void	nPuzzle::Solver::solveStepWorker(void)
{
	// Prevent solving of an already solved puzzle
	if (this->isSolved())
		return ;
	// Prevent solving of an unsolvable puzzle
	if (this->getSolvability() == nPuzzle::Solvability::UNSOLVABLE)
		return ;
	// Create first queue item from start position
	if (this->queue.size() == 0)
		this->processState(new nPuzzle::State(*this->puzzle.state));
	// Retrieve first element from queue
	nPuzzle::State*	current = this->popQueue();
	// Create upto 4 new states and process them
	for (nPuzzle::Direction direction : {
		nPuzzle::Direction::UP,
		nPuzzle::Direction::RIGHT,
		nPuzzle::Direction::DOWN,
		nPuzzle::Direction::LEFT,
	})
	{
		nPuzzle::State*	next = new nPuzzle::State(*current);
		if (next->move(direction))
		{
#warning shouldnt this be in move?
			next->setPrevious(current);
			this->processState(next);
		}
		else
			delete next;
	}
	// Check Solved State
	this->determineIsSolved();
}

void	nPuzzle::Solver::processState(nPuzzle::State* state)
{
TRACE_POSITION();
	// Calculate heuristics
	const nPuzzle::Board&	target = this->puzzle.getTarget().getBoard();
	if (this->getCalculateAllHeuristics())
		state->calculateAllHeuristics(target);
	else
		state->calculateOneHeuristic(target);
	// Store state in Queue
	this->addToQueue(state);
TRACE_POSITION();
}

void	nPuzzle::Solver::addToQueue(nPuzzle::State* state)
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	const nPuzzle::Board&	board = state->getBoard();
	auto found = this->visited.find(&board);
	if (found == this->visited.end())
	{
		this->owner.push_back(state);
		this->queue.emplace(state);
		this->visited.emplace(&board, state);
	}
	else if (found->second->getCost() > state->getCost())
	{
		this->owner.push_back(state);
		this->queue.emplace(state);
		found->second = state;
	}
	else
		delete state;
}

nPuzzle::State*	nPuzzle::Solver::popQueue(void)
{
	std::lock_guard<std::mutex>	lock(this->mutex);
	while (!this->queue.empty())
	{
		nPuzzle::State*	top = this->queue.top();
		this->queue.pop();
		auto found = this->visited.find(&top->getBoard());
		if (found == this->visited.end())
		{
			std::fprintf(stderr, "Took a board configuration from queue which did not exist in visited\n");
			this->visited.emplace(&top->getBoard(), top);
			// this->debugValidateQueueVisited();
			throw std::runtime_error("Took a board configuration from queue which did not exist in visited");
		}
		if (found->second == top)
			return (top);
	}
	return (nullptr);
}

size_t	nPuzzle::Solver::getQueueSize(void) const
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	return (this->queue.size());
}

int32_t	nPuzzle::Solver::getTopCost(void) const
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	if (this->queue.empty())
		return (this->puzzle.start->getCost());
	return (this->queue.top()->getCost());
}

int32_t	nPuzzle::Solver::getTopHeuristic(void) const
{
	std::lock_guard<std::mutex> lock(this->mutex);

	if (this->queue.empty())
		return (this->puzzle.state->getHeuristic(this->heuristicIndex));
	return (this->queue.top()->getHeuristic(this->heuristicIndex));
}

const nPuzzle::State&	nPuzzle::Solver::getTopState(void) const
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	if (this->queue.empty())
		return (*this->puzzle.state);
	return (*this->queue.top());
}

void	nPuzzle::Solver::solve(void)
{
	this->ensureActiveWorker();
	this->setCalculateAllHeuristics(false);
	this->setWorkerState(WorkerState::RUNALL);
}

bool	nPuzzle::Solver::solveStep(bool calculateAllHeuristics)
{
	this->ensureActiveWorker();
	this->setCalculateAllHeuristics(calculateAllHeuristics);
	this->setWorkerState(WorkerState::RUNONE);
	return (this->isSolved());
}

void	nPuzzle::Solver::determineIsSolved(void)
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	this->solved = !this->queue.empty() && this->queue.top()->getHeuristic(this->heuristicIndex) == 0;
	if (this->solved == true)
		this->workerState = WorkerState::IDLE;
}

bool	nPuzzle::Solver::isSolved(void)
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	return (this->solved);
}

void	nPuzzle::Solver::determineSolvability(void)
{
	const nPuzzle::Board&	target = this->puzzle.getTarget().getBoard();
	const nPuzzle::Board&	start = this->puzzle.getStartState().getBoard();

	// arrange both current and target puzzle in 1d Array;
	std::vector<int32_t>	start1D;
	std::vector<int32_t>	target1D;

	start1D.reserve(start.getSize());
	target1D.reserve(target.getSize());

	if (start.getWidth() != target.getWidth() || start.getHeight() != target.getHeight())
	{
		this->setSolvability(nPuzzle::Solvability::UNSOLVABLE);
		return ;
	}

	for (int32_t y = 0; y < target.getHeight(); ++y)
	{
		for (int32_t x = 0; x < target.getWidth(); ++x)
		{
			target1D.push_back(target.getTile(x,y).getVal());
			start1D.push_back(start.getTile(x, y).getVal());
		}
	}

	std::vector<int32_t> targetPosition(target1D.size(), -1);

	for (int32_t i = 0; i < target1D.size(); ++i){
		targetPosition[target1D[i]] = i;
	}

	int32_t	count = 0;

	for (int32_t sorted = 0; sorted + 1 < start1D.size(); ++sorted)
	{
		bool swapped = false;

		for (int32_t i = start1D.size() - 1; i > sorted; i--)
		{
			int32_t left = start1D[i - 1];
			int32_t right = start1D[i];

			if (targetPosition[left] > targetPosition[right])
			{
				std::swap(start1D[i - 1], start1D[i]);
				++count;
				swapped = true;
			}
		}

		if (!swapped)
			break;

	}

	const nPuzzle::Board::Tile&	startBlank = start.getEmptyTile();
	const nPuzzle::Board::Tile&	targetBlank = target.getEmptyTile();

	int32_t blankDistance = std::abs(startBlank.getX() - targetBlank.getX()) + std::abs(startBlank.getY() - targetBlank.getY());

	if (count % 2 == blankDistance % 2)
		this->setSolvability(nPuzzle::Solvability::SOLVABLE);
	else
		this->setSolvability(nPuzzle::Solvability::UNSOLVABLE);
}

nPuzzle::Solvability	nPuzzle::Solver::getSolvability(void) const
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	return (this->solvability.load());
}

void	nPuzzle::Solver::setSolvability(nPuzzle::Solvability val)
{
	std::lock_guard<std::mutex>	lock(this->mutex);

	this->solvability.store(val);
}

std::vector<const nPuzzle::State*>	nPuzzle::Solver::getSolution(void) const
{
	std::vector<const nPuzzle::State*>	path;
	std::lock_guard<std::mutex>	lock(this->mutex);

	if (this->queue.empty())
		return path;

	const nPuzzle::State * current = this->queue.top(); 

	if (current->getHeuristic(this->heuristicIndex) != 0)
		return path;

	while (current != nullptr)
	{
		path.push_back(current);
		current = current->getPrevious(); 
	}

	std::reverse(path.begin(), path.end());
	return path;
}

void	nPuzzle::Solver::clearQueue(void)
{
	this->stopWorker();
	std::lock_guard<std::mutex>	lock(this->mutex);

	for (nPuzzle::State* state: this->owner)
		delete state;
	this->owner.clear();
	this->queue = {};
	this->visited.clear();
}


/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

std::size_t	BoardPtrHash::operator()(const nPuzzle::Board* board) const noexcept
{
	return board->hash();
}

bool	BoardPtrEqual::operator()(const nPuzzle::Board* lhs,
							   const nPuzzle::Board* rhs) const noexcept
{
	return *lhs == *rhs;
}

bool	StateCompare::operator()(const nPuzzle::State* a, const nPuzzle::State* b) const
{
	return *a > *b;
}
