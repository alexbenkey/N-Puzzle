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

// nPuzzle::nPuzzle(void):
// 	width(0),
// 	height(0),
// 	size(0 * 0),
// 	target(nPuzzleTarget(this->width, this->height)),
// 	state(nPuzzleState(this->width, this->height))
// {
// 	std::cout	<< C_DGREEN	<< "Default constructor "
// 				<< C_GREEN	<< "nPuzzle"
// 				<< C_DGREEN	<< " called."
// 				<< C_RESET	<< std::endl;
// }


nPuzzle::nPuzzle(const int32_t size):
	width(size),
	height(size),
	size(size * size),
	target(nPuzzleTarget(this->width, this->height)),
	state(nPuzzleState(this->width, this->height))
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
	target(nPuzzleTarget(this->width, this->height)),
	state(nPuzzleState(this->width, this->height))
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
	if (row > this->height)
		throw std::runtime_error(std::string("Invalid puzzle row: "));
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
