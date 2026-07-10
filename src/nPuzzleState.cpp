/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzleState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/10 19:11:42 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleState.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzleState::nPuzzleState(const int32_t size):
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

nPuzzleState::nPuzzleState(const int32_t width, const int32_t height):
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

void	nPuzzleState::generateTiles(void)
{
	this->tiles.resize(this->height);
	for (int32_t y = 0; y < this->height; ++y)
		this->tiles[y].resize(this->width);
}

nPuzzleState::nPuzzleState(const nPuzzleState &src):
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

nPuzzleState::~nPuzzleState(void)
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

#include <iomanip>

void	nPuzzleState::printPuzzle(void) const
{
	if (validPuzzle())
		std::cout	<< "# Unknown puzzle solvability\n";
	else
		std::cout	<< "# This puzzle is unsolvable\n";
	if (getPuzzleHeight() != getPuzzleWidth())
		std::cout	<< "puzzle width " << getPuzzleWidth()	<< ' ';

	std::cout	<< getPuzzleHeight()	<< '\n';
	for (int32_t y = 0; y < getPuzzleHeight(); ++y)
	{
		for (int32_t x = 0; x < getPuzzleWidth(); ++x)
		{
			std::cout << std::setw(3) << tiles[y][x].getVal() << ' ';
		}
		std::cout << '\n';
	}
	std::cout	<< std::flush;
}

#include <set>

bool	nPuzzleState::validPuzzle(void) const
{
	return (validPuzzleContent() && validPuzzlePlacement());
}

bool	nPuzzleState::validPuzzleContent(void) const
{
	std::set<int32_t>	set;

	for (size_t y = 0; y < tiles.size(); ++y)
		for (size_t x = 0; x < tiles[y].size(); ++x)
			if (!set.insert(tiles[y][x].getVal()).second)
			{
				if (tiles[y][x].getVal() == 0)
					throw std::runtime_error("Duplicate 0 tile, probably incomplete puzzle");
				else
					throw std::runtime_error("Duplicate tile value");
			}
	if (*set.begin() != 0)
		throw std::runtime_error("Missing 0 tile");
	if (*set.rbegin() != this->size - 1)
		throw std::runtime_error(std::string("Out of bounds value "));
	if (set.size() != (size_t)this->size)
		throw std::runtime_error("Missing numbers");
	return (true);
}

bool	nPuzzleState::validPuzzlePlacement(void) const
{
	// Idont know, something with inversion and extra on even numbers
	// Spiral sucks
	return (true);
}

nPuzzleState::Tile&	nPuzzleState::getTile(int32_t value)
{
	if ((size_t)value > tiles.size()){
		std::runtime_error("Out of bounds Value");
	}
	for (size_t y = 0; y < this->tiles.size(); ++y)
	{
		for (size_t x = 0; x < this->tiles[y].size(); ++x)
		{
			if (this->tiles[y][x].getVal() == value)
				return (this->tiles[y][x]);
		}
	}
	return (this->tiles[0][0]);
}

void	nPuzzleState::printTilePos(const nPuzzleState::Tile& Tile) const
{
	std::cout	<< "Found tile with value: " << Tile.getVal()
				<< " at position [X,Y]:" << Tile.getxPos() << ", " << Tile.getyPos() << std::endl;
}

void 	nPuzzleState::moveTile(nPuzzleState::Tile& tile)
{
	// Check if the tile is adjacent to the empty square
	int32_t emptyX = emptyPos.x;
	int32_t emptyY = emptyPos.y;
	int32_t tileX = tile.getxPos();
	int32_t tileY = tile.getyPos();

	// check of tile is adjacent to empty square
	if ((abs(emptyX - tileX) == 1 && emptyY == tileY) || (abs(emptyY - tileY) == 1 && emptyX == tileX))
	{
		//swap the values of the empty tile and the given tile, update the empty position to the tile's position
		getTile(emptyX, emptyY).setVal(tile.getVal());
		tile.setVal(0);
		setEmptyPos(tileX, tileY);
	}
	else
		throw std::runtime_error("Tile is not adjacent to the empty square");
}

void nPuzzleState::moveUp(void)
{
	if (emptyPos.y == 0)
	{
		#ifdef DEBUG:
		std::cout	<< C_RED	<< "cannot move up, empty square is at the top"
					<< C_RESET	<< std::endl;
		#endif
		return;
	}
	Tile& tileAbove = getTile(emptyPos.x, emptyPos.y - 1);
	this->moveTile(tileAbove);
	this->increaseCost();
	#ifdef DEBUG:
	std::cout	<< C_GREEN	<< "Tile moved up successfully"
				<< C_RESET	<< std::endl;
	#endif
}

void nPuzzleState::moveDown(void)
{
	if (emptyPos.y == this->height - 1)
	{
		#ifdef DEBUG:
		std::cout	<< C_RED	<< "cannot move down, empty square is at the bottom"
					<< C_RESET	<< std::endl;
		#endif
		return;
	}
	Tile& tileBelow = getTile(emptyPos.x, emptyPos.y + 1);
	this->moveTile(tileBelow);
	this->increaseCost();
	#ifdef DEBUG:
	std::cout	<< C_GREEN	<< "Tile moved down successfully"
				<< C_RESET	<< std::endl;
	#endif
}

void nPuzzleState::moveLeft(void)
{
	if (emptyPos.x == 0)
	{
		#ifdef DEBUG:
		std::cout	<< C_RED	<< "cannot move left, empty square is at the left edge"
					<< C_RESET	<< std::endl;
		#endif
		return;
	}	
	Tile& tileLeft = getTile(emptyPos.x - 1, emptyPos.y);
	this->moveTile(tileLeft);
	this->increaseCost();
	#ifdef DEBUG:	
	std::cout	<< C_GREEN	<< "Tile moved left successfully"
				<< C_RESET	<< std::endl;
	#endif
}

void nPuzzleState::moveRight(void)
{
	if (emptyPos.x == this->width - 1)
	{
		#ifdef DEBUG:
		std::cout	<< C_RED	<< "cannot move right, empty square is at the right edge"
					<< C_RESET	<< std::endl;
		#endif
		return;
	}
	Tile& tileRight = getTile(emptyPos.x + 1, emptyPos.y);
	this->moveTile(tileRight);
	this->increaseCost();
	#ifdef DEBUG:
	std::cout	<< C_GREEN	<< "Tile moved right successfully"
				<< C_RESET	<< std::endl;
	#endif
}
/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

nPuzzleState	&nPuzzleState::operator=(const nPuzzleState &src)
{
	if (this == &src)
		return (*this);
	if (this->width != src.width || this->height != src.height)
		return (*this);
	this->tiles = src.tiles;
	return (*this);
}
