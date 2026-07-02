/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tile.cpp                                      :+:    :+:            */
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

nPuzzleState::Tile::Tile(void)
{
	this->value = 0;
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "Tile"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

nPuzzleState::Tile::Tile(const Tile &src)
{
	*this = src;
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< "Tile"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzleState::Tile::~Tile(void)
{
	std::cout	<< C_RED	<< "Deconstructor "
				<< C_RED	<< "Tile"
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
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

	return (*this);
}
