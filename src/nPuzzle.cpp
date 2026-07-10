/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzle.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "colors.hpp"

#include <iostream>
// std::

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
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "nPuzzle"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

nPuzzle::nPuzzle(const int32_t width, const int32_t height):
	width(width),
	height(height),
	size(width * height),
	start(nPuzzleState(this->width, this->height)),
	target(nPuzzleTarget(this->width, this->height)),
	state(this->start)
{
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "nPuzzle"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

nPuzzle::nPuzzle(const nPuzzle &src):
	width(src.width),
	height(src.height),
	size(src.size),
	start(src.start),
	target(src.target),
	state(src.state)
{
	*this = src;
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< "nPuzzle"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzle::~nPuzzle(void)
{
	std::cout	<< C_RED	<< "Deconstructor "
				<< C_RED	<< "nPuzzle"
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
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
