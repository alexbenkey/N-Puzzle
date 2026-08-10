/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:38:54 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/10 16:32:06 by ohengelm         ###   ########.fr       */
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

nPuzzle::State::State(const int32_t& width, const int32_t& height, const int32_t& size, const int32_t& heuristicIndex):
	width(width),
	height(height),
	size(size),
	heuristicIndex(heuristicIndex)
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
	heuristicIndex(src.heuristicIndex)
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

// #include <iomanip>

// void	nPuzzle::State::printPuzzle(void) const
// {
// 	if (validPuzzle())
// 		std::cout	<< "# Unknown puzzle solvability\n";
// 	else
// 		std::cout	<< "# This puzzle is unsolvable\n";
// 	if (getPuzzleHeight() != getPuzzleWidth())
// 		std::cout	<< "puzzle width " << getPuzzleWidth()	<< ' ';

// 	std::cout	<< getPuzzleHeight()	<< '\n';
// 	for (int32_t y = 0; y < getPuzzleHeight(); ++y)
// 	{
// 		for (int32_t x = 0; x < getPuzzleWidth(); ++x)
// 		{
// 			std::cout << std::setw(3) << tiles[y][x].getVal() << ' ';
// 		}
// 		std::cout << '\n';
// 	}
// 	std::cout	<< std::flush;
// }

#warning these functions are replaced by solvability
bool	nPuzzle::State::validPuzzle(void) const
{
	return (validPuzzleContent() && validPuzzlePlacement());
}

bool	nPuzzle::State::validPuzzleContent(void) const
{
	// std::set<int32_t>	set;

	// for (size_t y = 0; y < tiles.size(); ++y)
	// 	for (size_t x = 0; x < tiles[y].size(); ++x)
	// 		if (!set.insert(tiles[y][x].getVal()).second)
	// 		{
	// 			if (tiles[y][x].getVal() == 0)
	// 				throw std::runtime_error("Duplicate 0 tile, probably incomplete puzzle");
	// 			else
	// 				throw std::runtime_error("Duplicate tile value");
	// 		}
	// if (*set.begin() != 0)
	// 	throw std::runtime_error("Missing 0 tile");
	// if (*set.rbegin() != this->size - 1)
	// 	throw std::runtime_error(std::string("Out of bounds value "));
	// if (set.size() != (size_t)this->size)
	// 	throw std::runtime_error("Missing numbers");
	return (true);
}

bool	nPuzzle::State::validPuzzlePlacement(void) const
{
#warning this was the note I couldnt find again XD
	// Idont know, something with inversion and extra on even numbers
	// Spiral sucks
	return (true);
}

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t value) const
{
	return (this->board.getTile(value));
}

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t x, const int32_t y) const
{
	return (this->board.getTile(x, y));
}

// void	nPuzzle::State::printTilePos(const nPuzzle::Board::Tile& Tile) const
// {
// 	std::cout	<< "Found tile with value: " << Tile.getVal()
// 				<< " at position [X,Y]:" << Tile.getxPos() << ", " << Tile.getyPos() << std::endl;
// }

void	nPuzzle::State::moveTile(const nPuzzle::Board::Tile& tile)
{
	// Check if the tile is adjacent to the empty square
	int32_t	emptyX = emptyPos.x;
	int32_t	emptyY = emptyPos.y;
	int32_t	tileX = tile.getX();
	int32_t	tileY = tile.getY();

	// check of tile is adjacent to empty square
	if ((abs(emptyX - tileX) == 1 && emptyY == tileY) || (abs(emptyY - tileY) == 1 && emptyX == tileX))
	{
		//swap the values of the empty tile and the given tile, update the empty position to the tile's position
		this->board.swapTiles(emptyX, emptyY, tileX, tileY);
	}
	else
		throw std::runtime_error("Tile is not adjacent to the empty square");
}

bool	nPuzzle::State::move(Direction direction)
{
	bool	moved = this->board.move(direction);
	if (moved == true)
		this->increaseCost();
	return (moved);
}

bool	nPuzzle::State::sameBoard(const State &rhs) const noexcept
{
	if (this == &rhs)
		return (true);
	return (this->board == rhs.board);
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

void	nPuzzle::State::calculateOneHeuristic(const nPuzzle::Board& target, int32_t h)
{
	this->heuristic[h] = heuristic::getHeuristic(h, this->board, target);
}

int32_t	nPuzzle::State::getHeuristic(int32_t h) const
{
	return (this->heuristic.count(h) ? this->heuristic.at(h) : -1);
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
	this->emptyPos = src.emptyPos;
	this->cost = src.cost;
	this->heuristic = src.heuristic;
	this->score = src.score;
	this->searchMode = src.searchMode;
	return (*this);
}

std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state)
{
	os << "# unknown solvability\n";
	os << state.board;

	return os;
}
