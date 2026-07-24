/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Board.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:58:21 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/24 16:54:40 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Board.hpp"
#include "nPuzzle.Board.Tile.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::Board::Board(void):
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
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzle::Board::~Board(void)
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

void	nPuzzle::Board::setSize(const int32_t w, const int32_t h)
{
	if (w <= 0 || h <= 0)
		throw std::invalid_argument("Invalid board size");
	// if (w == this->width && h == this->height)
	// 	return ;

	this->clearTiles();
	this->width = w;
	this->height = h;
	this->size = w * h;
	this->TilesByPos.resize(this->size, nullptr);
	this->TilesByVal.resize(this->size);
}

const int32_t	nPuzzle::Board::getWidth(void) const
{
	return (this->width);
}

const int32_t	nPuzzle::Board::getHeight(void) const
{
	return (this->height);
}

const int32_t	nPuzzle::Board::getSize(void) const
{
	return (this->size);
}

const nPuzzle::Board::Tile&	nPuzzle::Board::getTile(const int32_t value) const
{
	return (*this->TilesByVal.at(value).get());
}

const nPuzzle::Board::Tile&	nPuzzle::Board::getTile(const int32_t x, const int32_t y) const
{
	return (*this->TilesByPos.at(y * this->width + x));
}

const nPuzzle::Board::Tile&	nPuzzle::Board::getEmptyTile(void) const
{
	return (*this->TilesByVal.at(0).get());
}

void	nPuzzle::Board::addTile(const int32_t value, const int32_t x, const int32_t y)
{
	if (value < 0 || value >= this->size)
		throw std::out_of_range("Tile value out of range");
	if (x < 0 || x >= this->width ||
		y < 0 || y >= this->height)
		throw std::out_of_range("Tile position out of bounds");
	if (TilesByVal[value] != nullptr)
		throw std::runtime_error("Tile value is already set");
	int32_t	pos = y * this->width + x;
	if (TilesByPos[pos] != nullptr)
		throw std::runtime_error("Tile position is already taken");

	// Create unique pointer to ensure proper ownership
	std::unique_ptr<Tile> tile(new Tile(value, x, y));
	// Track pointer because TilesByVal must be set first in case it throws an error
	Tile*	tilePtr = tile.get();
	// Actually store the pointers
	this->TilesByVal[value] = std::move(tile);
	this->TilesByPos[pos] = tilePtr;
}
void	nPuzzle::Board::move(const int32_t direction)
{
	throw std::runtime_error("I need logic!");
}

void	nPuzzle::Board::swapTiles(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2)
{
	int32_t	pos1 = y1 * this->width + x1;
	int32_t	pos2 = y2 * this->width + x2;
	
	// Swapping Tile coordinates.
	nPuzzle::Board::Tile*	tile1 = this->TilesByPos.at(pos1);
	nPuzzle::Board::Tile*	tile2 = this->TilesByPos.at(pos2);
	tile1->swapCoords(*tile2);
	// Swapping Tile in coordinate container
	std::swap(this->TilesByPos[pos1], this->TilesByPos[pos2]);
}

void	nPuzzle::Board::clearTiles(void)
{
	for (std::unique_ptr<nPuzzle::Board::Tile> &tile : this->TilesByVal)
		tile.reset();
	for (nPuzzle::Board::Tile *&tile : TilesByPos)
		tile = nullptr;
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

nPuzzle::Board&	nPuzzle::Board::operator=(const Board& src)
{
	if (this == &src)
		return *this;

	this->clearTiles();

	this->width = src.width;
	this->height = src.height;
	this->size = src.size;

	this->TilesByVal.resize(this->size);
	this->TilesByPos.resize(this->size, nullptr);

	for (const auto& tile : src.TilesByVal)
	{
		if (tile != nullptr)
		{
			this->addTile(
				tile->getVal(),
				tile->getX(),
				tile->getY()
			);
		}
	}

	return *this;
}

std::ostream&	operator<<(std::ostream& os, const nPuzzle::Board& board)
{
	for (int32_t i = 0; i < board.size; i++)
	{
		nPuzzle::Board::Tile* tile = board.TilesByPos.at(i);
		if (tile)
			os	<< *tile;
		else
			os	<< '-';

		if ((i + 1) % board.width == 0)
			os << '\n';
		else
			os << ' ';
	}
	// os << "TilesByVal:\n";

	// for (int32_t i = 0; i < board.size; i++)
	// {
	// 	const auto& tile = board.TilesByVal.at(i);

	// 	os << i << ": ";

	// 	if (tile)
	// 	{
	// 		os << tile->getVal()
	// 		<< " (" << tile->getX()
	// 		<< ", " << tile->getY()
	// 		<< ")";
	// 	}
	// 	else
	// 	{
	// 		os << "nullptr";
	// 	}

	// 	os << '\n';
	// }


	// os << "\nTilesByPos:\n";

	// for (int32_t i = 0; i < board.size; i++)
	// {
	// 	nPuzzle::Board::Tile* tile = board.TilesByPos.at(i);

	// 	os << i << ": ";

	// 	if (tile)
	// 	{
	// 		os << tile->getVal()
	// 		<< " (" << tile->getX()
	// 		<< ", " << tile->getY()
	// 		<< ")";
	// 	}
	// 	else
	// 	{
	// 		os << "nullptr";
	// 	}

	// 	os << '\n';
	// }

	return os;
}
