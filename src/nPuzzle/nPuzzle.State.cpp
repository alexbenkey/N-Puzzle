/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:38:54 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:47:04 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.State.hpp"
#include "nPuzzle.Board.Tile.hpp"

#include "colors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::State::State(void):
	width(0),
	height(0),
	size(0)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->generateTiles();
}

nPuzzle::State::State(const int32_t size):
	width(size),
	height(size),
	size(size * size)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->generateTiles();
}

nPuzzle::State::State(const int32_t width, const int32_t height):
	width(width),
	height(height),
	size(width * height)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->generateTiles();
}

void	nPuzzle::State::generateTiles(void)
{
	this->board.setSize(this->width, this->height);
	// this->tiles.resize(this->height);
	// for (int32_t y = 0; y < this->height; ++y)
	// 	this->tiles[y].resize(this->width);
}

nPuzzle::State::State(const State &src):
	width(src.getPuzzleWidth()),
	height(src.getPuzzleHeight()),
	size(src.getPuzzleSize())
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

#include <set>

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
	// Idont know, something with inversion and extra on even numbers
	// Spiral sucks
	return (true);
}

// nPuzzle::Board::Tile&	nPuzzle::State::getTile(int32_t value)
// {
// 	if ((size_t)value > tiles.size()){
// 		std::runtime_error("Out of bounds Value");
// 	}
// 	for (size_t y = 0; y < this->tiles.size(); ++y)
// 	{
// 		for (size_t x = 0; x < this->tiles[y].size(); ++x)
// 		{
// 			if (this->tiles[y][x].getVal() == value)
// 				return (this->tiles[y][x]);
// 		}
// 	}
// 	return (this->tiles[0][0]);
// }

bool nPuzzle::State::setUsedHeuristic(int32_t value)
{
	if (value < 0 || value >= this->heuristic.size())
		return false;

	this->usedHeuristic = value;
	return true;
}

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t value) const
{
	return (this->board.getTile(value));
	// if ((size_t)value > tiles.size()){
	// 	std::runtime_error("Out of bounds Value");
	// }
	// for (size_t y = 0; y < this->tiles.size(); ++y)
	// {
	// 	for (size_t x = 0; x < this->tiles[y].size(); ++x)
	// 	{
	// 		if (this->tiles[y][x].getVal() == value)
	// 			return (this->tiles[y][x]);
	// 	}
	// }
	// return (this->tiles[0][0]);
}

// nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t x, const int32_t y)
// {
// 	return (this->board.getTile(x, y));
// 	// return tiles[y][x];
// }

const nPuzzle::Board::Tile&	nPuzzle::State::getTile(const int32_t x, const int32_t y) const
{
	return (this->board.getTile(x, y));
	// return tiles[y][x];
}

// void	nPuzzle::State::printTilePos(const nPuzzle::Board::Tile& Tile) const
// {
// 	std::cout	<< "Found tile with value: " << Tile.getVal()
// 				<< " at position [X,Y]:" << Tile.getxPos() << ", " << Tile.getyPos() << std::endl;
// }

int32_t	nPuzzle::State::getTileValue(const int32_t x, const int32_t y) const
{
	return (this->board.getTile(x, y).getVal());
	// return tiles[y][x].getVal();
}

void 	nPuzzle::State::moveTile(const nPuzzle::Board::Tile& tile)
{
	// Check if the tile is adjacent to the empty square
	int32_t emptyX = emptyPos.x;
	int32_t emptyY = emptyPos.y;
	int32_t tileX = tile.getX();
	int32_t tileY = tile.getY();

	// check of tile is adjacent to empty square
	if ((abs(emptyX - tileX) == 1 && emptyY == tileY) || (abs(emptyY - tileY) == 1 && emptyX == tileX))
	{
		//swap the values of the empty tile and the given tile, update the empty position to the tile's position
		this->board.swapTiles(emptyX, emptyY, tileX, tileY);
		// getTile(emptyX, emptyY).setVal(tile.getVal());
		// tile.setVal(0);
		// setEmptyPos(tileX, tileY);
	}
	else
		throw std::runtime_error("Tile is not adjacent to the empty square");
}

bool nPuzzle::State::move(Direction direction){
	const nPuzzle::Board::Tile *toMove = nullptr; 
	emptyPos.y = getEmptyTile().getY();
	emptyPos.x = getEmptyTile().getX();

	switch (direction){

		case Direction::UP:
			if (emptyPos.y == 0)
			{
				#if DEBUG >= DEBUG_TRACE
				std::cout	<< C_RED	<< "cannot move up, empty square is at the top"
							<< C_RESET	<< std::endl;
				#endif
				return false;
			}
			toMove = &getTile(emptyPos.x, emptyPos.y - 1);
			break ;
		case Direction::RIGHT:
			if (emptyPos.x == this->width - 1)
			{
				#if DEBUG >= DEBUG_TRACE
				std::cout	<< C_RED	<< "cannot move right, empty square is at the right edge"
							<< C_RESET	<< std::endl;
				#endif
				return false;
			}
			toMove = &getTile(emptyPos.x + 1, emptyPos.y);
			break ;

		case(Direction::DOWN):
			if (emptyPos.y == this->height - 1)
			{
				#if DEBUG >= DEBUG_TRACE
				std::cout	<< C_RED	<< "cannot move down, empty square is at the bottom"
							<< C_RESET	<< std::endl;
				#endif
				return false;
			}
			toMove =  &getTile(emptyPos.x, emptyPos.y + 1);
			break ;

		case(Direction::LEFT):
			if (emptyPos.x == 0)
			{
				#if DEBUG >= DEBUG_TRACE
				std::cout	<< C_RED	<< "cannot move left, empty square is at the left edge"
							<< C_RESET	<< std::endl;
				#endif
				return false;
			}
			toMove =  &getTile(emptyPos.x - 1, emptyPos.y);
			break ;
	}
		
	this->moveTile(*toMove);
	this->increaseCost();
	#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_GREEN	<< "Tile moved successfully"
				<< C_RESET	<< std::endl;
	#endif
	return (true);
}

bool	nPuzzle::State::sameState(const State &rhs) const noexcept
{
	if (this == &rhs)
		return (true);
	// possibly an excessive check (?), but avoids potential bounds issues.
	if (this->width != rhs.width || this->height != rhs.height)
		return (false);
	for (int32_t y = 0; y < this->height; ++y)
		for (int32_t x = 0; x < this->width; ++x)
			if (this->board.getTile(x, y).getVal() != rhs.board.getTile(y, x).getVal())
			// if (this->tiles[y][x].getVal() != rhs.tiles[y][x].getVal())
				return (false);
	return (true);
}

void	nPuzzle::State::calculateHeuristic(const nPuzzle::Board& target)
{
	for (int32_t h = 0; h < heuristic::size; ++h)
		this->calculateHeuristic(h, target);
}

void	nPuzzle::State::calculateHeuristic(int32_t h, const nPuzzle::Board& target)
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
 	int32_t hKey = this->usedHeuristic;
	const int32_t lhsScore =
		this->getCost() + this->getHeuristic(hKey);
	const int32_t rhsScore =
		rhs.getCost() + rhs.getHeuristic(hKey);

	std::cout << "called < operator" << std::endl;
	std::cout << "cost lhs: " << this->getCost() << "heuristic lhs: " << this->getHeuristic(hKey) << " Score lhs: " << lhsScore << std::endl;
	std::cout << "cost rhs: " << rhs.getCost() << "heuristic rhs: " << rhs.getHeuristic(hKey) << " Score rhs: " << rhsScore << std::endl << std::endl << std::endl;

	if (lhsScore != rhsScore)
		return lhsScore < rhsScore;
	
	// if ((this->getCost() + this->getHeuristic(hKey)) != (rhs.getCost() + rhs.getHeuristic(hKey)))
	// 	return ;
	return (this->getCost() < rhs.getCost());
	// 	return true;
	// return false; 
}

bool	nPuzzle::State::operator<=(const State &rhs) const noexcept
{
 	int32_t hKey = this->usedHeuristic;
	std::cout << "called <= operator" << std::endl;
	std::cout << "cost lhs: " << this->getCost() << "heuristic lhs: " << this->getHeuristic(hKey) << std::endl;
	std::cout << "cost rhs: " << rhs.getCost() << "heuristic rhs: " << rhs.getHeuristic(hKey) << std::endl << std::endl << std::endl;
	if ((this->getCost() + this->getHeuristic(hKey)) <= (rhs.getCost() + rhs.getHeuristic(hKey))){
		return true;
	}	
	else if (this->getCost() <= rhs.getCost())
		return true;
	return false; 
}

bool	nPuzzle::State::operator>(const State &rhs) const noexcept
{
 	int32_t hKey = this->usedHeuristic;
	std::cout << "called > operator" << std::endl;
	std::cout << "cost lhs: " << this->getCost() << "heuristic lhs: " << this->getHeuristic(hKey) << std::endl;
	std::cout << "cost rhs: " << rhs.getCost() << "heuristic rhs: " << rhs.getHeuristic(hKey) << std::endl << std::endl << std::endl;
	if ((this->getCost() + this->getHeuristic(hKey)) > (rhs.getCost() + rhs.getHeuristic(hKey)))
		return 1;
	else if (this->getCost() > rhs.getCost())
		return 1;
	return 0; 
}
bool	nPuzzle::State::operator>=(const State &rhs) const noexcept
{
 	int32_t hKey = this->usedHeuristic;
	std::cout << "called >= operator" << std::endl;
	std::cout << "cost lhs: " << this->getCost() << "heuristic lhs: " << this->getHeuristic(hKey) << std::endl;
	std::cout << "cost rhs: " << rhs.getCost() << "heuristic rhs: " << rhs.getHeuristic(hKey) << std::endl << std::endl << std::endl;
	if ((this->getCost() + this->getHeuristic(hKey)) > (rhs.getCost() + rhs.getHeuristic(hKey)))
		return 1;
	else if (this->getCost() > rhs.getCost())
		return 1;
	return 0; 
}

nPuzzle::State	&nPuzzle::State::operator=(const State &src)
{
	if (this == &src)
		return (*this);
	// if (this->width != src.width || this->height != src.height)
	// 	return (*this);
	this->width = src.width;
	this->height = src.height;
	this->size = this->width * this->height;
	this->board = src.board;
	// this->tiles = src.tiles;
	this->emptyPos = src.emptyPos;
	this->cost = src.cost;
	this->heuristic = src.heuristic;
	this->usedHeuristic = src.usedHeuristic;
	return (*this);
}

std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state)
{
	os << "# unknown solvability\n";
	os << state.board;

	return os;
}
