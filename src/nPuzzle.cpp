/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/22 14:39:55 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "colors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream
#include <algorithm>	// std::sort

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::nPuzzle(const int32_t size):
	width(size),
	height(size),
	size(size * size),
	start(nPuzzleState(this->width, this->height)),
	target(nPuzzleTarget(this->width, this->height)),
	state(this->start)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

nPuzzle::nPuzzle(const int32_t width, const int32_t height):
	width(width),
	height(height),
	size(width * height),
	start(nPuzzleState(this->width, this->height)),
	target(nPuzzleTarget(this->width, this->height)),
	state(this->start)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

nPuzzle::nPuzzle(const nPuzzle &src):
	width(src.width),
	height(src.height),
	size(src.size),
	start(src.start),
	target(src.target),
	state(src.state)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	*this = src;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzle::~nPuzzle(void)
{
	this->resetStates();
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_RED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
#endif
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	nPuzzle::setRow(int32_t row, const std::vector<int>& numbers)
{
	if (row < 0 || row >= this->height)
		throw std::runtime_error(std::string("Invalid puzzle row: "));
	if (numbers.size() != static_cast<size_t>(this->width))
		throw std::runtime_error(std::string("Invalid number of tiles in row "));
	for (int32_t x = 0; x < this->width; ++x)
	{
		this->state.getTile(x, row).setVal(numbers[x]);
		if (numbers[x] == 0)
			this->state.setEmptyPos(x, row);
		this->state.getTile(x, row).setxPos(x);
		this->state.getTile(x, row).setyPos(row);
	}
}

nPuzzleState&	nPuzzle::getQueueState(void)
{
	if (this->queueIndex == -1)
		return (this->state);
	else
		return (*this->queue.at(this->queueIndex));
}

void	nPuzzle::maintainValidQueue(void)
{
	size_t	size = this->queue.size();

	if (size == 0)
		this->queueIndex = -1;
	else if (this->queueIndex < 0)
		this->queueIndex = 0;
	else if (this->queueIndex >= (int32_t)size)
		this->queueIndex = size - 1;

#if DEBUG >= DEBUG_DEBUG
	std::cerr	<< __func__	<< '['	<< __LINE__	<< ']'
				<< "queueIndex: "	<< this->queueIndex
				<< std::endl;
#endif
}

#warning needs to be adjusted to use the enum with this->state.move(enum)
bool	nPuzzle::move(nPuzzleState::Direction direction, int32_t h)
{
	bool	validMove;

	validMove = this->state.move(direction);
	if (validMove)
	{
		if (h != -1)
			this->calculateHeuristic(h);
		else
			this->calculateHeuristic();
	}
	return (validMove);
}

void	nPuzzle::solve(int32_t h)
{
	if (h >= heuristic::size)
		return ;
#warning needs to validate puzzle solved state
	// while puzzle is unsolved
	while (true)
		this->solveStep(h);
}

void	nPuzzle::solveStep(int32_t h)
{
#if DEBUG >= DEBUG_DEBUG
	std::printf("%s[%i]\n", __func__, __LINE__);
#endif

#warning needs to validate puzzle solved state
	// if puzzle is solved
	if (false)
		return ;

	if (this->queue.size() == 0)
		this->processState(new nPuzzleState(this->state), h);

	nPuzzleState*	current = this->queue.front();
	this->queue.erase(this->queue.begin());
	if (current->sameState(this->target))
		return ;
	this->visited.push_back(current);
	for (nPuzzleState::Direction direction : {
			nPuzzleState::Direction::UP,
			nPuzzleState::Direction::RIGHT,
			nPuzzleState::Direction::DOWN,
			nPuzzleState::Direction::LEFT
		}) {
			nPuzzleState*	next = new nPuzzleState(*current);
			if (next->move(direction))
				this->processState(next, h);
			else
				delete next;
		}

	this->maintainValidQueue();
#if DEBUG >= DEBUG_DEBUG
	std::printf("%s[%i] queue.size = %lu\n", __func__, __LINE__, this->queue.size());
#endif
}

void	nPuzzle::processState(nPuzzleState* state, int32_t h)
{
	if (this->stateHasAlreadyBeenVisited(state))
		return ;
	if (this->stateIsAlreadyInQueue(state))
		return ;
	state->calculateHeuristic(h, &this->target);
	this->queue.push_back(state);
	std::sort(this->queue.begin(), this->queue.end());
}

bool	nPuzzle::stateHasAlreadyBeenVisited(nPuzzleState* state)
{
	std::vector<nPuzzleState*>::iterator	foundItem;

	foundItem = std::find(this->visited.begin(), this->visited.end(), state);
	if (foundItem == this->visited.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->visited.erase(foundItem);
		return (false);
	}
	return (true);
}

bool	nPuzzle::stateIsAlreadyInQueue(nPuzzleState* state)
{
	std::vector<nPuzzleState*>::iterator	foundItem;

	foundItem = std::find(this->queue.begin(), this->queue.end(), state);
	if (foundItem == this->queue.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->queue.erase(foundItem);
		return (false);
	}
	return (true);
}

void	nPuzzle::calculateHeuristic(void)
{
	for (int32_t h = 0; h < heuristic::size; ++h)
		this->state.calculateHeuristic(h, &this->target);
}

void	nPuzzle::calculateHeuristic(int32_t h)
{
	this->state.calculateHeuristic(h, &this->target);
}

void	nPuzzle::printAllTiles(const nPuzzleState& state) const
{
	for (int32_t x = 0, width = state.getPuzzleWidth(); x < width; ++x)
	{
		for (int32_t y = 0, height = state.getPuzzleHeight(); y < height; ++y)
		{
			nPuzzleState::Tile tile = state.getTile(x, y);
			std::printf("%2i [%2i][%2i] ", tile.getVal(), tile.getxPos(), tile.getyPos());
			state.printTilePos(tile);
		}
	}
	std::cout	<< std::endl;
}

void	nPuzzle::printAllTilesFlex(nPuzzleState& state)
{
	// for (int32_t x = 0, width = state.getPuzzleWidth(); x < width; ++x)
	// {
	// 	for (int32_t y = 0, height = state.getPuzzleHeight(); y < height; ++y)
	// 	{

	// 		nPuzzleState::Tile tile = state.getTile(x, y);
	// 		std::printf("[%2i][%2i] > %2i [%2i][%2i] ", x, y, tile.getVal(), tile.getxPos(), tile.getyPos());
	// 		state.printTilePos(tile);
	// 	}
	// }
	for (int32_t value = 1, size = state.getPuzzleSize(); value < size; ++value)
	{
		nPuzzleState::Tile tile = state.getTile(value);
		std::printf("%2i [%2i][%2i] ", tile.getVal(), tile.getxPos(), tile.getyPos());
		state.printTilePos(tile);
	}
	std::cout	<< std::endl;
}

void	nPuzzle::resetStates(void)
{
	this->clearStates();
	this->state = this->start; 
}

void	nPuzzle::clearStates(void)
{
	for (nPuzzleState *state : this->queue)
		delete state;
	this->queue.clear();
	for (nPuzzleState *state : this->visited)
		delete state;
	this->visited.clear();

	this->queueIndex = -1;
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

nPuzzle	&nPuzzle::operator=(const nPuzzle &src)
{
	if (this == &src)
		return (*this);

	return (*this);
}
