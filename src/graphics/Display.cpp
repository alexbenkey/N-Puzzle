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

#define MARGIN 23

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
	SetWindowPosition(MARGIN, MARGIN);
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
	this->Frame.x = GetRenderWidth() - this->Frame.width - MARGIN;
	this->Frame.y = GetRenderHeight() - this->Frame.height - MARGIN;
	this->tile.width = this->Frame.width / this->cols;
	this->tile.height = this->Frame.height / this->rows;
}

// void	Display::render()
// {
// 	ClearBackground(ORANGE);
// 	DrawRectangleRec(this->Frame, Color{23, 23, 23, 255});
// 	DrawText("nPuzzle", MARGIN, MARGIN, 20, WHITE);
// 	DrawText("[S] Display Start", MARGIN, MARGIN * 2, 20, RED);
// 	DrawText("[T] Display Target", MARGIN, MARGIN * 3, 20, WHITE);

// 	int	xOffset = (this->tile.width - 20) / 2;
// 	int	yOffset = (this->tile.height - 20) / 2;
// 	for (int i = 0; i < this->cols * this->rows; ++i)
// 	{
// 		this->tile.x = this->Frame.x + (i / this->cols * this->tile.width);
// 		this->tile.y = this->Frame.y + (i % this->cols * this->tile.height);
// 		DrawRectangleRec(this->tile, Color{(unsigned char)((int)this->tile.x % 256), (unsigned char)((int)this->tile.y % 256), 0, 255});
// 		DrawRectangleLinesEx(this->tile, 2, Color{23, 23, 23, 127});
// 		DrawText(std::to_string(i).c_str(), this->tile.x + xOffset, this->tile.y + yOffset, 20, BLUE);
// 	}
// }

void	Display::renderHUD()
{
	ClearBackground(Color{255, 127, 0, 255});
	DrawRectangleRec(this->Frame, Color{23, 23, 23, 255});
	DrawText("nPuzzle", MARGIN, MARGIN, 20, WHITE);
	DrawText("[S] Display Start", MARGIN, MARGIN * 2, 20, RED);
	DrawText("[T] Display Target", MARGIN, MARGIN * 3, 20, WHITE);
}

void	Display::renderTiles()
{
	int	xOffset = (this->tile.width - 20) / 2;
	int	yOffset = (this->tile.height - 20) / 2;
	for (int i = 0; i < this->cols * this->rows; ++i)
	{
		if (i == 0)
			continue;
		this->tile.x = this->Frame.x + (i % this->cols * this->tile.width);
		this->tile.y = this->Frame.y + (i / this->cols * this->tile.height);
		DrawRectangleRec(this->tile, Color{(unsigned char)((int)this->tile.x % 256), (unsigned char)((int)this->tile.y % 256), 0, 255});
		DrawRectangleLinesEx(this->tile, 2, Color{23, 23, 23, 127});
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
