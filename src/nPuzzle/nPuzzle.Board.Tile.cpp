/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Board.Tile.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:58:21 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:47:08 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Board.Tile.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::Board::Tile::Tile(const int32_t value, const int32_t x, const int32_t y):
	value(value),
	x(x),
	y(y)
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

nPuzzle::Board::Tile::~Tile(void)
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

void			nPuzzle::Board::Tile::setVal(const int32_t val)
{
	this->value = val;
}

const int32_t	nPuzzle::Board::Tile::getVal(void) const
{
	return (this->value);
}

void			nPuzzle::Board::Tile::setX(const int32_t x)
{
	this->x = x;
}

const int32_t	nPuzzle::Board::Tile::getX(void) const
{
	return (this->x);
}

void			nPuzzle::Board::Tile::setY(const int32_t y)
{
	this->y = y;
}

const int32_t	nPuzzle::Board::Tile::getY(void) const
{
	return (this->y);
}

void	nPuzzle::Board::Tile::swapCoords(Tile& other)
{
	std::swap(this->x, other.x);
	std::swap(this->y, other.y);
}
/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

std::ostream&	operator<<(std::ostream& os, const nPuzzle::Board::Tile& tile)
{
	os << tile.value;
	return os;
}
