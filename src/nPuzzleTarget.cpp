/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzleTarget.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleTarget.hpp"
#include "colors.hpp"

#include <iostream>
// std::

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzleTarget::nPuzzleTarget(const int32_t width, const int32_t height):
	nPuzzleState(width, height)
{
	this->setTargetTiles();
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "nPuzzleTarget"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

// nPuzzleTarget::nPuzzleTarget(const nPuzzleTarget &src)
// {
// 	*this = src;
// 	std::cout	<< C_DGREEN	<< "Copy constructor "
// 				<< C_GREEN	<< "nPuzzleTarget"
// 				<< C_DGREEN	<< " called."
// 				<< C_RESET	<< std::endl;
// }

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

// nPuzzleTarget::~nPuzzleTarget(void)
// {
// 	std::cout	<< C_RED	<< "Deconstructor "
// 				<< C_RED	<< "nPuzzleTarget"
// 				<< C_DRED	<< " called"
// 				<< C_RESET	<< std::endl;
// }

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	nPuzzleTarget::setTargetTiles(void)
{
	int32_t top = 0;
	int32_t bottom = this->height - 1;
	int32_t left = 0;
	int32_t right = this->width - 1;

	int32_t i = 1;

	while (i < this->size)
	{
		// left → right
		for (int32_t x = left; x <= right && i < this->size; ++x)
			this->getTile(x, top).set(i++);
		++top;

		// top → bottom
		for (int32_t y = top; y <= bottom && i < this->size; ++y)
			this->getTile(right, y).set(i++);
		--right;

		// right → left
		for (int32_t x = right; x >= left && i < this->size; --x)
			this->getTile(x, bottom).set(i++);
		--bottom;

		// bottom → top
		for (int32_t y = bottom; y >= top && i < this->size; --y)
			this->getTile(left, y).set(i++);
		++left;
	}
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

// nPuzzleTarget	&nPuzzleTarget::operator=(const nPuzzleTarget &src)
// {
// 	if (this == &src)
// 		return (*this);

// 	return (*this);
// }
