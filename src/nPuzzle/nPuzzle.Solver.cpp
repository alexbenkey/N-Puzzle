/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:52:09 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/04 17:52:24 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Solver.hpp"
#include "nPuzzle.State.hpp"
#include "nPuzzle.Target.hpp"
#include "nPuzzle.Board.hpp"

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
#endif
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	nPuzzle::Solver::setHeuristic(int32_t h)
{
	this->heuristic = h;
}

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
#warning unsolvable not implemented
	// Create first queue item for starting position
	if (this->queue.size() == 0)
		this->processState(new nPuzzle::State(*this->puzzle.state), calculateAllHeuristics);
	// Retrieve first element from queue
	nPuzzle::State*	current = this->popQueue();
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
		{
			next->setPrevious(current);
			this->processState(next, calculateAllHeuristics);
		}
		else
			delete next;
	}
#if DEBUG >= DEBUG_DEBUG
	// print queue
	// this->printQueueStatus();
#endif
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

void	nPuzzle::Solver::addToQueue(nPuzzle::State* state)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
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
	std::lock_guard<std::mutex>	lock(this->queueMutex);

	while (!this->queue.empty())
	{
		nPuzzle::State*	top = this->queue.top();
		this->queue.pop();
		auto found = this->visited.find(&top->getBoard());
		if (found == this->visited.end())
		{
			std::fprintf(stderr, "Took a board configuration from queue which did not exist in visited\n");
			this->visited.emplace(&top->getBoard(), top);
			this->debugValidateQueueVisited();
			throw std::runtime_error("Took a board configuration from queue which did not exist in visited");
		}
		if (found->second == top)
			return (top);
	}
	return (nullptr);
}

void nPuzzle::Solver::debugValidateQueueVisited()
{
	while (!this->queue.empty())
	{
		nPuzzle::State* top = this->queue.top();
		this->queue.pop();

		const nPuzzle::Board* board = &top->getBoard();

		std::size_t lookupHash = BoardPtrHash{}(board);
		std::size_t lookupBucket = this->visited.bucket(board);

		auto found = this->visited.find(board);
		if (found != this->visited.end())
		{
			continue;
		}

		std::cerr	<< "################################\n"
					<< "Queue node not found\n"
					<< "Board ptr: "		<< board		<< '\n'
					<< "Hash:      "		<< lookupHash	<< '\n'
					<< "Board:\n"
					<< *board
					<< std::endl;

		std::cerr	<< "Bucket contents:\n"
					<< "Bucket:    "		<< lookupBucket	<< '\n'
					<< "Buckets:   "		<< this->visited.bucket_count() << '\n'
					<< "Visited:   "		<< this->visited.size() << '\n'
					<< std::flush;

		for (auto it = this->visited.begin(lookupBucket);
			 it != this->visited.end(lookupBucket);
			 ++it)
		{
			const nPuzzle::Board* storedBoard = it->first;

			std::cerr	<< "Bucket\n"
						<< "  Stored ptr: "	<< storedBoard << '\n'
						<< "  Stored hash: "	<< BoardPtrHash{}(storedBoard) << '\n'
						<< "  Equal:       "	<< BoardPtrEqual{}(storedBoard, board) << '\n'
						<< "  Same ptr:    "	<< (storedBoard == board) << '\n'
						<< *storedBoard	<< '\n'
						<< std::flush;
		}

		std::cerr << "Manual scan:\n";

		bool manualFound = false;
		for (const auto i : this->visited)
		{
			const nPuzzle::Board*	storedBoard = i.first;
			const nPuzzle::State*	state = i.second;

			bool equal = (*storedBoard == *board);
			bool samePtr = (storedBoard == board);
			bool sameHash = (storedBoard->hash() == board->hash());

			if (equal)
			{
				manualFound = true;

				std::size_t storedBucket = visited.bucket(storedBoard);

				std::cerr	<< "MANUAL MATCH FOUND\n"
							<< "Stored ptr:   "	<< storedBoard	<< '\n'
							<< "Lookup ptr:   "	<< board		<< '\n'
							<< "Stored hash:  "	<< storedBoard->hash() << '\n'
							<< "Lookup hash:  "	<< board->hash() << '\n'
							<< "Same ptr:     "	<< samePtr << '\n'
							<< "Same hash:    "	<< sameHash << '\n'
							<< "Equal:        "	<< equal << '\n'
							<< "Stored state: "	<< state << '\n'
							<< "Lookup state: "	<< top << '\n'
							<< "Stored bucket:"	<< storedBucket	<< '\n'
							<< "Lookup bucket:"	<< lookupBucket	<< '\n'
							<< "Bucket match: "	<< (storedBucket == lookupBucket) << '\n'
							<< "Board:\n"
							<< *storedBoard
							<< std::endl;

				std::cerr << "Walking stored bucket:\n";

				bool foundSelf = false;
				for (auto it = this->visited.begin(storedBucket);
					 it != this->visited.end(storedBucket);
					 ++it)
				{
					std::cerr	<< "  Node\n"
								<< "    ptr:       " << it->first << '\n'
								<< "    hash:      " << BoardPtrHash{}(it->first) << '\n'
								<< "    same ptr:  " << (it->first == storedBoard) << '\n'
								<< "    equal:     " << BoardPtrEqual{}(it->first, storedBoard) << '\n'
								<< std::flush;

					if (it->first == storedBoard)
						foundSelf = true;
				}

				std::cerr	<< "Stored node reachable from bucket: "
							<< foundSelf
							<< std::endl;

				auto refind = this->visited.find(storedBoard);

				std::cerr	<< "find(storedPtr): "
							<< (refind != this->visited.end())
							<< '\n';

				if (refind != this->visited.end())
				{
					std::cerr	<< "Returned ptr: "
								<< refind->first
								<< '\n'
								<< "Returned state: "
								<< refind->second
								<< std::endl;
				}
			}
		}

		if (!manualFound)
		{
			std::cerr << "NO MANUAL MATCH FOUND" << std::endl;
		}

		std::cerr << "Queue state:\n"
				  << "State ptr: " << top << '\n'
				  << "Cost:      " << top->getCost() << '\n'
				  << std::endl;

		delete top;
	}
}

size_t	nPuzzle::Solver::getQueueSize(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);
	return (this->queue.size());
}

const nPuzzle::State&	nPuzzle::Solver::getTopState(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);

	if (this->queue.empty())
		return (*this->puzzle.state);
	return (*this->queue.top());
}

int32_t	nPuzzle::Solver::getTopCost(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);

	if (this->queue.empty())
		return (this->puzzle.start->getCost());
	return (this->queue.top()->getCost());
}

int32_t	nPuzzle::Solver::getTopHeuristic(void) const
{
	std::lock_guard<std::mutex> lock(this->queueMutex);

	if (this->queue.empty())
		return (this->puzzle.state->getHeuristic(this->heuristic));
	return (this->queue.top()->getHeuristic(this->heuristic));
}

bool	nPuzzle::Solver::isSolved(void) const
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);

	return (!this->queue.empty() && this->queue.top()->getHeuristic(this->heuristic) == 0);
}

std::vector<const nPuzzle::State*>	nPuzzle::Solver::getSolution(void) const
{
	std::vector<const nPuzzle::State*> path;
	std::lock_guard<std::mutex>	lock(this->queueMutex);

	if (this->queue.empty())
		return path;
	
	const nPuzzle::State * current = this->queue.top(); 

	if (current->getHeuristic(this->heuristic) != 0)
		return path;

	while (current != nullptr)
	{
		path.push_back(current);
		current = current->getPrevious(); 
	}

	std::reverse(path.begin(), path.end());
	return path;
}

void	nPuzzle::Solver::printQueueStatus(void) const
{
	{
		std::lock_guard<std::mutex>	lock(this->queueMutex);

		std::fprintf(stderr, "# Queue[%lu]\n", this->queue.size());
		if (!this->queue.empty())
		{
			const nPuzzle::State*	top = this->queue.top();
			int32_t	g = top->getCost();
			int32_t	h = top->getHeuristic(this->heuristic);
			std::fprintf(stderr, "#  %-16p g:%3i h:%3i f:%3i\n", top, g, h, g + h);
			std::fflush(stderr);
			std::cerr	<< *top	<< std::endl;
		}
	}
	if (this->isSolved())
		std::fprintf(stderr, "#  Puzzle is Solved");
}

void	nPuzzle::Solver::clearQueue(void)
{
	std::lock_guard<std::mutex>	lock(this->queueMutex);

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
