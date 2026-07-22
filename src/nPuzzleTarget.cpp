/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzleTarget.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/22 16:55:55 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleTarget.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzleTarget::nPuzzleTarget(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setTargetTiles();
}

nPuzzleTarget::nPuzzleTarget(const int32_t width, const int32_t height):
	nPuzzleState(width, height)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setTargetTiles();
}

// nPuzzleTarget::nPuzzleTarget(const nPuzzleTarget &src)
// {
// 	*this = src;
// 	std::cout	<< C_DGREEN	<< "Copy constructor "
// 				<< C_GREEN	<< __func__
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
// 				<< C_RED	<< __func__
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
	int32_t bottom = getPuzzleHeight() - 1;
	int32_t left = 0;
	int32_t right = getPuzzleWidth() - 1;

	int32_t i = 1;

	while (i < getPuzzleSize())
	{
		// left → right
		for (int32_t x = left; x <= right && i < getPuzzleSize(); ++x)
			this->getTile(x, top).setContent(i++, x, top);
		++top;

		// top → bottom
		for (int32_t y = top; y <= bottom && i < getPuzzleSize(); ++y)
			this->getTile(right, y).setContent(i++, right, y);
		--right;

		// right → left
		for (int32_t x = right; x >= left && i < getPuzzleSize(); --x)
			this->getTile(x, bottom).setContent(i++, x, bottom);
		--bottom;

		// bottom → top
		for (int32_t y = bottom; y >= top && i < getPuzzleSize(); --y)
			this->getTile(left, y).setContent(i++, left, y);
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
