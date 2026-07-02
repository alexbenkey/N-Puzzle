/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Display.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/02 17:58:28 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/07/02 17:58:28 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>
// std::

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

Display::Display(void)
{
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< "Display"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
	SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "nPuzzle");
	SetWindowPosition(23, 23);
	SetWindowMinSize(800, 450);
	this->cols = 5;
	this->rows = 5;
	this->adjustScale();
}

Display::Display(const Display &src)
{
	*this = src;
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< "Display"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

Display::~Display(void)
{
	std::cout	<< C_RED	<< "Deconstructor "
				<< C_RED	<< "Display"
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	Display::adjustScale()
{
	this->Frame.width = GetRenderWidth() - MeasureText("[T] Display Target", 20) - 69;
	this->Frame.height = GetRenderHeight() - 46;
	this->Frame.x = GetRenderWidth() - this->Frame.width - 23;
	this->Frame.y = GetRenderHeight() - this->Frame.height - 23;
	this->tile.width = this->Frame.width / this->cols;
	this->tile.height = this->Frame.height / this->rows;
}

void	Display::render()
{
	ClearBackground(ORANGE);
	DrawRectangleRec(this->Frame, Color{23, 23, 23, 255});
	DrawText("nPuzzle", 23, 23, 20, WHITE);
	DrawText("[S] Display Start", 23, 46, 20, RED);
	DrawText("[T] Display Target", 23, 69, 20, WHITE);

	int	xOffset = (this->tile.width - 20) / 2;
	int	yOffset = (this->tile.height - 20) / 2;
	for (int i = 0; i < this->cols * this->rows; ++i)
	{
		this->tile.x = this->Frame.x + (i / this->cols * this->tile.width);
		this->tile.y = this->Frame.y + (i % this->cols * this->tile.height);
		DrawRectangleRec(this->tile, Color{(unsigned char)((int)this->tile.x % 256), (unsigned char)((int)this->tile.y % 256), 0, 255});
		DrawRectangleLinesEx(this->tile, 2, Color{23,23,23,127});
		DrawText(std::to_string(i).c_str(), this->tile.x + xOffset, this->tile.y + yOffset, 20, BLUE);
	}
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

Display	&Display::operator=(const Display &src)
{
	if (this == &src)
		return (*this);

	return (*this);
}
