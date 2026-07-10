/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/10 20:04:19 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "colors.hpp"

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

void	nPuzzle::solve(void)
{
	nPuzzleState*	current;
	nPuzzleState*	next;

	this->processState(new nPuzzleState(this->state));
	while(this->queue.size())
	{
		current = this->queue.front();
		this->queue.erase(this->queue.begin());
#warning needs == overload
		if (false)
		// if (*current == this->target)
			break ;
		this->visited.push_back(current);
		for (auto move : {
			&nPuzzleState::moveDown,
			&nPuzzleState::moveUp,
			&nPuzzleState::moveLeft,
			&nPuzzleState::moveRight
		}){
			next = new nPuzzleState(*current);
			(next->*move)();
			this->processState(next);
		}
	}
}

void	nPuzzle::processState(nPuzzleState* state)
{
	if (this->stateHasAlreadyBeenVisited(state))
		return ;
	if (this->stateIsAlreadyInQueue(state))
		return ;
	switch (1)
	{
		case 1:
			this->calculateHeuristic(state, this);
			break;
		default:
			break;
	}
	this->queue.push_back(state);
#warning sorting requires proper < overload
	// std::sort(this->queue.begin(), this->queue.end());
}

bool	nPuzzle::stateHasAlreadyBeenVisited(nPuzzleState* state)
{
	std::vector<nPuzzleState*>::iterator	foundItem;

	foundItem = std::find(this->visited.begin(), this->visited.end(), state);
	if (foundItem == this->visited.end())
		return (false);
// #warning requires state cost
// 	if (false)
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
// #warning requires state cost
	// if (false)
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->queue.erase(foundItem);
		return (false);
	}
	return (true);
}

#warning passing nPuzzle as argument for now, because heursitcs might be extracted from class
void	nPuzzle::calculateHeuristic(nPuzzleState* state, nPuzzle* puzzle)
{
	nPuzzleState	target = puzzle->getTargetState();
	int	width = puzzle->getWidth();
	int	height = puzzle->getHeight();
	int	heuristic = 0;

	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)
			if (state->getTile(x, y).getVal() != target.getTile(x, y).getVal())
				++heuristic;
#warning need to actuall set heursitc
	// state.setH(heuristic);
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
