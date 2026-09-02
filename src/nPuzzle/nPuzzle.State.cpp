/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:38:54 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/02 18:23:07 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.State.hpp"
#include "nPuzzle.Board.Tile.hpp"

#include "colors.hpp"
#include "heuristic.hpp"
#include "Errors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::State::State(const nPuzzle& puzzle):
	width(puzzle.width),
	height(puzzle.height),
	size(puzzle.size),
	heuristicIndex(puzzle.heuristicIndex),
	searchMode(puzzle.mode)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->board.setSize(this->width, this->height);
}

nPuzzle::State::State(const State &src):
	width(src.width),
	height(src.height),
	size(src.size),
	heuristicIndex(src.heuristicIndex),
	searchMode(src.searchMode)
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

nPuzzle::State::~State(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DRED	<< "Deconstructor "
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

void	nPuzzle::State::addTile(const int32_t value, const int32_t x, const int32_t y)
{
	this->board.addTile(value, x, y);
}

int32_t	nPuzzle::State::getPuzzleSize(void) const
{
	return this->size;
}

int32_t	nPuzzle::State::getPuzzleHeight(void) const
{
	return this->height;
}

int32_t	nPuzzle::State::getPuzzleWidth(void) const
{
	return this->width;
}

const nPuzzle::Board&	nPuzzle::State::getBoard() const
{
	return this->board;
}

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t value) const
{
	return (this->board.getTile(value));
}

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t x, const int32_t y) const
{
	return (this->board.getTile(x, y));
}

const nPuzzle::Board::Tile&	nPuzzle::State::getEmptyTile() const
{
	return this->board.getEmptyTile();
}

bool	nPuzzle::State::sameBoard(const State &rhs) const noexcept
{
	if (this == &rhs)
		return (true);
	return (this->board == rhs.board);
}

bool	nPuzzle::State::move(Direction direction)
{
	bool	moved = this->board.move(direction);
	if (moved == true)
		this->increaseCost();
	return (moved);
}

void	nPuzzle::State::increaseCost(void)
{
	++this->cost;
};

int32_t	nPuzzle::State::getCost(void) const
{
	return (this->cost);
}

void	nPuzzle::State::calculateAllHeuristics(const nPuzzle::Board& target)
{
	for (int32_t h = 0; h < heuristic::size; ++h)
		this->calculateOneHeuristic(target, h);
}

void	nPuzzle::State::calculateOneHeuristic(const nPuzzle::Board& target)
{
	this->calculateOneHeuristic(target, this->heuristicIndex);
}

void	nPuzzle::State::calculateOneHeuristic(const nPuzzle::Board& target, int32_t h) const
{
TRACE_POSITION("%i %s", h, heuristic::function[h].name);
	this->heuristic[h] = heuristic::getHeuristic(h, this->board, target);
	switch (this->heuristic[h])
	{
		case -2:
			this->addPendingHeuristic(h, target);
			break;
		default:
			break;
	}
}

int32_t	nPuzzle::State::getHeuristic(int32_t h) const
{
TRACE_POSITION("%i", h);
	this->checkPendingHeuristic(h);
	return (this->heuristic.count(h) ? this->heuristic.at(h) : -1);
}

void	nPuzzle::State::addPendingHeuristic(int32_t h, const nPuzzle::Board& target) const
{
	this->pending[h] = target;
}

void	nPuzzle::State::checkPendingHeuristic(int32_t h) const
{
	std::map<int32_t, nPuzzle::Board>::iterator	found = this->pending.find(h);
	if (found == this->pending.end())
		return;
TRACE_POSITION();
	nPuzzle::Board	target = std::move(found->second);
	this->pending.erase(found);
	this->calculateOneHeuristic(target, h);
}

void	nPuzzle::State::clearPendingHeuristics(void)
{
	this->heuristic.clear();
	this->pending.clear();
}


void	nPuzzle::State::setPrevious(nPuzzle::State *state)
{
	this->previous = state;
}

const nPuzzle::State*	nPuzzle::State::getPrevious(void) const
{
	return this->previous;
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

bool	nPuzzle::State::operator<(const State &rhs) const noexcept
{
	#warning it is now required to set the particular used heuristic in the state class.

	int32_t	lhsHeuristic = 0;
	int32_t	rhsHeuristic = 0;
	int32_t	lhsCost = 0;
	int32_t	rhsCost = 0;
	int32_t	lhsScore = 0;
	int32_t	rhsScore = 0;

	switch (this->searchMode)
	{
		case (nPuzzle::searchMode::ASTAR):
			// std::cout << "using ASTAR heuristic for comparison" << std::endl;
			lhsHeuristic = this->getHeuristic(this->heuristicIndex);
			rhsHeuristic = rhs.getHeuristic(rhs.heuristicIndex);
			lhsCost = this->cost;
			rhsCost = rhs.cost;
			break ;

		case (nPuzzle::searchMode::GREEDY):
			// std::cout << "using GREEDY heuristic for comparison" << std::endl;
			lhsHeuristic = this->getHeuristic(this->heuristicIndex);
			rhsHeuristic = rhs.getHeuristic(rhs.heuristicIndex);
			break ;

		case (nPuzzle::searchMode::UNIFORM):
			// std::cout << "using UNIFORM heuristic for comparison" << std::endl;
			lhsCost = this->cost;
			rhsCost = rhs.cost;
			break ;
	}

	lhsScore = lhsCost + lhsHeuristic;
	rhsScore = rhsCost + rhsHeuristic;

	if (lhsScore != rhsScore)
		return lhsScore < rhsScore;

	if (lhsHeuristic != rhsHeuristic)
		return lhsHeuristic < rhsHeuristic;

	return false;
}

bool	nPuzzle::State::operator<=(const State &rhs) const noexcept
{
	return !(rhs < *this);
}

bool	nPuzzle::State::operator>(const State &rhs) const noexcept
{
	return (rhs < *this);
}
bool	nPuzzle::State::operator>=(const State &rhs) const noexcept
{
	return !(*this < rhs);
}

nPuzzle::State	&nPuzzle::State::operator=(const State &src)
{
	if (this == &src)
		return (*this);
	if (this->width != src.width || this->height != src.height)
		throw std::invalid_argument(std::string(
			"Cannot assign State: dimension mismatch w: ") + 
			std::to_string(this->width) + "/" + std::to_string(src.width) + ", h: " + 
			std::to_string(this->height) + "/" + std::to_string(src.height));
	this->board = src.board;
	// this->emptyPos = src.emptyPos;
	this->cost = src.cost;
	this->heuristic = src.heuristic;
	this->score = src.score;
	return (*this);
}

std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state)
{
	os << "# unknown solvability\n";
	os << state.board;

	return os;
}
