/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzleState.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleState.hpp"
#include "colors.hpp"

#include <iostream>
// std::

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
	this->generateTiles();
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "nPuzzleState"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

nPuzzleState::nPuzzleState(const int32_t width, const int32_t height):
	width(width),
	height(height),
	size(width * height)
{
	this->generateTiles();
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "nPuzzleState"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

void	nPuzzleState::generateTiles(void)
{
	this->tiles.resize(this->height);
	for (int32_t y = 0; y < this->height; ++y)
		this->tiles[y].resize(this->width);
}

nPuzzleState::nPuzzleState(const nPuzzleState &src):
	width(src.width),
	height(src.height),
	size(src.size)
{
	*this = src;
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< "nPuzzleState"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzleState::~nPuzzleState(void)
{
	std::cout	<< C_RED	<< "Deconstructor "
				<< C_RED	<< "nPuzzleState"
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

#include <iomanip>

void	nPuzzleState::printPuzzle(void) const
{
	if (this->validPuzzle())
		std::cout	<< "# Unknown puzzle solvability\n";
	else
		std::cout	<< "# This puzzle is unsolvable\n";
	if (this->width != this->height)
		std::cout	<< this->width	<< ' ';
	std::cout	<< this->height	<< '\n';
	for (size_t y = 0; y < this->tiles.size(); ++y)
	{
		for (size_t x = 0; x < this->tiles[y].size(); ++x)
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
	std::set<int32_t>				set;

	for (size_t y = 0; y < this->tiles.size(); ++y)
		for (size_t x = 0; x < this->tiles[y].size(); ++x)
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
	if ((size_t)value > this->tiles.size()){
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
	int32_t emptyX = this->Emptysquare->getxPos();
	int32_t emptyY = this->Emptysquare->getyPos();
	int32_t tileX = tile.getxPos();
	int32_t tileY = tile.getyPos();

	if ((abs(emptyX - tileX) == 1 && emptyY == tileY) || (abs(emptyY - tileY) == 1 && emptyX == tileX))
	{

		// Swap the values of the empty square and the tile
		int32_t tempVal = this->Emptysquare->getVal();
		this->Emptysquare->setVal(tile.getVal());
		tile.setVal(tempVal);

		// Update the position of the empty square
		this->setEmptysquare(&tile);
	}
	else
	{
		throw std::runtime_error("Tile is not adjacent to the empty square");
	}
}

void nPuzzleState::moveUp(void)
{
	if (this->Emptysquare->getyPos() == 0)
		throw std::runtime_error("Cannot move up, empty square is at the top");
	Tile& tileAbove = this->getTile(this->Emptysquare->getxPos(), this->Emptysquare->getyPos() - 1);
	this->moveTile(tileAbove);
}

void nPuzzleState::moveDown(void)
{
	if (this->Emptysquare->getyPos() == this->height - 1)
		throw std::runtime_error("Cannot move down, empty square is at the bottom");
	Tile& tileBelow = this->getTile(this->Emptysquare->getxPos(), this->Emptysquare->getyPos() + 1);
	this->moveTile(tileBelow);
}

void nPuzzleState::moveLeft(void)
{
	if (this->Emptysquare->getxPos() == 0)
		throw std::runtime_error("Cannot move left, empty square is at the left edge");
	Tile& tileLeft = this->getTile(this->Emptysquare->getxPos() - 1, this->Emptysquare->getyPos());
	this->moveTile(tileLeft);
}

void nPuzzleState::moveRight(void)
{
	if (this->Emptysquare->getxPos() == this->width - 1)
		throw std::runtime_error("Cannot move right, empty square is at the right edge");
	Tile& tileRight = this->getTile(this->Emptysquare->getxPos() + 1, this->Emptysquare->getyPos());
	this->moveTile(tileRight);
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
