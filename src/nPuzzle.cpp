/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/10 13:58:06 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

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
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

nPuzzle::nPuzzle(const int32_t width, const int32_t height):
	width(width),
	height(height),
	size(width * height),
	start(nPuzzleState(this->width, this->height)),
	target(nPuzzleTarget(this->width, this->height)),
	state(this->start)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

nPuzzle::nPuzzle(const nPuzzle &src):
	width(src.width),
	height(src.height),
	size(src.size),
	start(src.start),
	target(src.target),
	state(src.state)
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

nPuzzle::~nPuzzle(void)
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

void	nPuzzle::setRow(int32_t row, const std::vector<int>& numbers)
{
	if (row > this->height)
		throw std::runtime_error(std::string("Invalid puzzle row: "));
	for (int32_t x = 0; x < this->width; ++x)
	{
		this->state.getTile(x, row).setVal(numbers[x]);
		if (numbers[x] == 0)
			this->state.setEmptysquare(&this->state.getTile(x, row));
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
