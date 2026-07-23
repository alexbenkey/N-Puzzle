/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzleTile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:55 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 14:21:14 by ohengelm         ###   ########.fr       */
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

nPuzzleState::Tile::Tile(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->value = 0;
}

nPuzzleState::Tile::Tile(const Tile &src)
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

nPuzzleState::Tile::~Tile(void)
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


/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

nPuzzleState::Tile	&nPuzzleState::Tile::operator=(const Tile &src)
{
	if (this == &src)
		return (*this);
	this->value = src.value;
	this->xPos = src.xPos;
	this->yPos = src.yPos;
	return (*this);
}
