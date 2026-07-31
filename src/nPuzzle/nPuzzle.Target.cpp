/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle::Target.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 14:21:14 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.Target.hpp"

#include "colors.hpp"
#include "Errors.hpp"

#include <iostream>	// std::stream

// /** ************************************************************************ **\
//  * 
//  * 	Constructors
//  * 
// \* ************************************************************************** */

// nPuzzle::Target::Target(void)
// {
// #if DEBUG >= DEBUG_TRACE
// 	std::cout	<< C_DGREEN	<< "Default constructor "
// 				<< C_GREEN	<< __func__
// 				<< C_DGREEN	<< " called."
// 				<< C_RESET	<< std::endl;
// #endif
// 	this->setTargetTiles();
// }

nPuzzle::Target::Target(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
}

nPuzzle::Target::Target(const int32_t width, const int32_t height)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setSize(width, height);
}

nPuzzle::Target::Target(const nPuzzle::Target &src)
{
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
	*this = src;
}

// /** ************************************************************************ **\
//  * 
//  * 	Deconstructors
//  * 
// \* ************************************************************************** */

// // nPuzzle::Target::~nPuzzle::Target(void)
// // {
// // 	std::cout	<< C_RED	<< "Deconstructor "
// // 				<< C_RED	<< __func__
// // 				<< C_DRED	<< " called"
// // 				<< C_RESET	<< std::endl;
// // }

// /** ************************************************************************ **\
//  * 
//  * 	Member Functions
//  * 
// \* ************************************************************************** */

void	nPuzzle::Target::setSize(const int32_t w, const int32_t h)
{
	this->board.setSize(w, h);
	this->setTargetTiles();
}

// void	nPuzzle::Target::setTargetTiles(void)
// {
// 	int32_t top = 0;
// 	int32_t bottom = this->board.getHeight() - 1;
// 	int32_t left = 0;
// 	int32_t right = this->board.getWidth() - 1;
// 	int32_t	size = this->board.getSize();
// std::fprintf(stderr, "Creating Target\n");
// 	for (int32_t i = 1; i < size;)
// 	{
// 		// left → right
// 		for (int32_t x = left; x <= right && i < size; ++x)
// 			this->board.addTile(i++, x, top);
// 		++top;

// 		// top → bottom
// 		for (int32_t y = top; y <= bottom && i < size; ++y)
// 			this->board.addTile(i++, right, y);
// 		--right;

// 		// right → left
// 		for (int32_t x = right; x >= left && i < size; --x)
// 			this->board.addTile(i++, x, bottom);
// 		--bottom;

// 		// bottom → top
// 		for (int32_t y = bottom; y >= top && i < size; --y)
// 			this->board.addTile(i++, left, y);
// 		++left;
// 	}
// std::fprintf(stderr, "Done looping Target top %i bottom %i left %i right %i\n", top, left, bottom, right);
// 	this->board.addTile(0, right, top);
// std::fprintf(stderr, "Done creating Target\n");
// }
void nPuzzle::Target::setTargetTiles(void)
{
    int32_t top    = 0;
    int32_t bottom = this->board.getHeight() - 1;
    int32_t left   = 0;
    int32_t right  = this->board.getWidth() - 1;

    int32_t i = 1;
    const int32_t size = this->board.getSize();

	while (top <= bottom && left <= right)
	{
		// left -> right
		for (int32_t x = left; x <= right; ++x, ++i)
			this->board.addTile(i == size ? 0 : i, x, top);
		++top;
		if (top > bottom) break;

		// top -> bottom
		for (int32_t y = top; y <= bottom; ++y, ++i)
			this->board.addTile(i == size ? 0 : i, right, y);
		--right;
		if (left > right) break;

		// right -> left
		for (int32_t x = right; x >= left; --x, ++i)
			this->board.addTile(i == size ? 0 : i, x, bottom);
		--bottom;
		if (top > bottom) break;

		// bottom -> top
		for (int32_t y = bottom; y >= top; --y, ++i)
			this->board.addTile(i == size ? 0 : i, left, y);
		++left;
	}
}

const nPuzzle::Board&	nPuzzle::Target::getBoard(void) const
{
	return (this->board);
}

// /** ************************************************************************ **\
//  * 
//  * 	Operators
//  * 
// \* ************************************************************************** */

nPuzzle::Target	&nPuzzle::Target::operator=(const nPuzzle::Target &src)
{
	if (this == &src)
		return (*this);
	this->board = src.board;
	return (*this);
}

std::ostream&	operator<<(std::ostream& os, const nPuzzle::Target& target)
{
	os << "# target\n";
	os << target.board;

	return os;
}
