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

Display::Display(nPuzzle* puzzle): puzzle(puzzle)
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
	// this->cols = 5;
	// this->rows = 5;
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
	this->tile.width = this->Frame.width / this->puzzle->getWidth();
	this->tile.height = this->Frame.height / this->puzzle->getHeight();
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

void	Display::renderTiles(nPuzzleState& state)
{
	Color	ctile = {192, 192, 192, 255};
	int	xOffset = (this->tile.width - 20) / 2;
	int	yOffset = (this->tile.height - 20) / 2;

	for (int x = 0; x < this->puzzle->getWidth(); ++x)
	{
		this->tile.x = this->Frame.x + x * this->tile.width;
		for (int y = 0; y < this->puzzle->getHeight(); ++y)
		{
			this->tile.y = this->Frame.y + y * this->tile.height;
			int	val = state.getTileValue(x, y);
			if (val == 0)
				continue;
			if (val == this->puzzle->getTargetState().getTileValue(x, y))
			ctile = {69, 69, 69, 255};
			else
			ctile = {123, 123, 123, 255};
			DrawRectangleRec(this->tile, ctile);
			DrawRectangleLinesEx(this->tile, 2, Color{23, 23, 23, 127});
			DrawText(std::to_string(val).c_str(), this->tile.x + xOffset, this->tile.y + yOffset, 20, ORANGE);
		}
	}
	// for (int i = 0; i < this->puzzle->getSurface(); ++i)
	// {
	// 	if (i == 0)
	// 		continue;
	// 	this->tile.x = this->Frame.x + (i % this->puzzle->getWidth() * this->tile.width);
	// 	this->tile.y = this->Frame.y + (i / this->puzzle->getWidth() * this->tile.height);
	// 	DrawRectangleRec(this->tile, Color{(unsigned char)((int)this->tile.x % 256), (unsigned char)((int)this->tile.y % 256), 0, 255});
	// 	DrawRectangleLinesEx(this->tile, 2, Color{23, 23, 23, 127});
	// 	DrawText(std::to_string(i).c_str(), this->tile.x + xOffset, this->tile.y + yOffset, 20, BLUE);
	// }
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
