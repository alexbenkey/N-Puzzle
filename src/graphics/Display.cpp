/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:58:28 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/03 18:20:27 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>
// std::

std::unordered_map<char, std::string> Display::hotkeyList = {
	{ 'S', "Display Start" },
	{ 'T', "Display Target" },
	{ 'R', "Reset to Start" },
};

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
	this->setFontSize(DEFAULT_FONTSIZE);
	this->setMargin(DEFAULT_MARGIN);
	this->adjustScale();
	SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "nPuzzle");

	this->setFontSize(DEFAULT_FONTSIZE);
	this->setMargin(DEFAULT_MARGIN);
	SetWindowPosition(DEFAULT_MARGIN, DEFAULT_MARGIN);
	SetWindowMinSize(800, 450);
	SetWindowSize(800, 450);
	// this->cols = 5;
	// this->rows = 5;
	// this->adjustScale();
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
	// set to minimum size
	this->configureMinimumSizes();
	SetWindowMinSize(this->HUD.width + this->Frame.width + 3 * this->margin, this->HUD.height + 2 * this->margin);
	// Set sizes
	this->Frame.width = GetRenderWidth() - this->HUD.width - this->margin * 3;
	this->tile.width = this->Frame.width / this->puzzle->getWidth();
	this->tile.height = this->Frame.height / this->puzzle->getHeight();
	// Set locations
	this->HUD.x = this->margin;
	this->HUD.y = this->margin;
	this->HUDData.x = this->HUD.x;
	this->HUDData.y = this->HUD.y;
	this->HUDControls.x = this->HUD.x;
	this->HUDControls.y = this->HUDData.y + this->HUDData.height;
	this->Frame.x = this->HUD.x + this->HUD.width + this->margin;
	this->Frame.y = this->margin;


	// this->Frame.width = GetRenderWidth() - MeasureText("[T] Display Target", 20) - 69;
	// this->Frame.height = GetRenderHeight() - 46;
	// this->Frame.x = GetRenderWidth() - this->Frame.width - this->margin;
	// this->Frame.y = GetRenderHeight() - this->Frame.height - this->margin;
	// this->tile.width = this->Frame.width / this->puzzle->getWidth();
	// this->tile.height = this->Frame.height / this->puzzle->getHeight();
	// getMinHUDWidth();
}

void	Display::configureMinimumSizes()
{
	configureMinimumHUDSizes();
	configureMinimumFrameSizes();
	if (this->Frame.height < this->HUD.height)
		this->Frame.height = this->HUD.height;
	else
		this->HUD.height = this->Frame.height;
}

void	Display::getMinHUDWidth()
{
	int	width;

	this->HUDControls.width = this->getMinHUDKeyWidth() + this->getMinHUDDescriptionWidth();
	this->HUDControls.height = Display::hotkeyList.size() * this->fontHeight;
	this->HUD.width = this->HUDControls.width;
	this->HUD.height = this->HUDControls.height;
	// width = this->getMinHUDKeyWidth() + this->getMinHUDDescriptionWidth();
	// if (width != 0)
	// 	width += this->margin;
	// float height = MeasureTextEx(GetFontDefault(), "-", 20, 0).y;
	// TraceLog(LOG_WARNING, "w %i h %f", width, height);
}

int	Display::getMinHUDKeyWidth()
{
	int width = 0;

	for (const auto& key : Display::hotkeyList)
	{
		std::string text = "[" + std::string(1, key.first) + "]";
		width = std::max(width, MeasureText(text.c_str(), 20));
	}
	return width;
}

int	Display::getMinHUDDescriptionWidth()
{
	int width = 0;

	for (const auto& key : Display::hotkeyList)
		width = std::max(width, MeasureText(key.second.c_str(), 20));
	return width;
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
	DrawText("nPuzzle", this->margin, this->margin, 20, WHITE);
	DrawText("[S] Display Start", this->margin, this->margin * 2, 20, RED);
	DrawText("[T] Display Target", this->margin, this->margin * 3, 20, WHITE);
}

void	Display::renderTiles(nPuzzleState& state)
{
	Color	tileColor = {192, 192, 192, 255};
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
				tileColor = {69, 69, 69, 255};
			else
				tileColor = {123, 123, 123, 255};
			DrawRectangleRec(this->tile, tileColor);
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
