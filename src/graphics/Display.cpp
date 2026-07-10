/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:58:28 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/09 18:47:51 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>	// std::

std::unordered_map<char, std::string> Display::hotkeyList = {
	{ 'R', "Reset to Start" },
	{ 'T', "Display Target" },
	{ 'S', "Display Start" },
};

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

Display::Display(nPuzzle* puzzle): puzzle(puzzle)
{
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;

	//Configuration and initialitation of raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(DEFAULT_MARGIN, DEFAULT_MARGIN, "nPuzzle");

	// Setting default values for font and margin
	//	includeHUD = true, because HUD.fontHeight wasnt properly set before InitWindow()
	this->setFontSize(DEFAULT_FONTSIZE, false, true);
	this->setMargin(DEFAULT_MARGIN, false, false);

	// Configure to actual puzzle
	this->setPuzzle(this->puzzle);
}

// Display::Display(const Display &src)
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

Display::~Display(void)
{
	std::cout	<< C_DRED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	Display::setPuzzle(nPuzzle* puzzle)
{
	this->puzzle = puzzle;

	// Configuration of Areas
	this->configureMinimumSizes();
	this->configureMaximumSizes();
	this->configureScreen();
	this->configureSizes();
	this->configurePositions();
}

void	Display::configureMinimumSizes(void)
{
	int	width;
	int	height;

	this->HUD.configureSizes();
	this->configureMinimumFrameSizes();
	width = this->HUD.width() + this->Frame.width + this->margin * 3;
	height = std::max(this->HUD.height(), this->Frame.height) + this->margin * 2;
	TraceLog(LOG_INFO, "Setting MinWindow: %4ix%-4i", width, height);
	SetWindowMinSize(width, height);
}

void	Display::configureMinimumFrameSizes()
{
	this->tile.width = (float)MeasureText("WW", this->fontSize) + 2 * this->margin;
	this->tile.height = this->fontSize + 2 * margin;
	Display::logRectangle("tile", this->tile);

	this->Frame.width = this->tile.width * (float)this->puzzle->getWidth();
	this->Frame.width = std::min(this->Frame.width, (float)GetMonitorWidth(GetCurrentMonitor()) - this->HUD.width());
	this->Frame.height = this->tile.height * this->puzzle->getHeight();
	this->Frame.height = std::min(this->Frame.height, (float)GetMonitorHeight(GetCurrentMonitor()) - 2 * this->margin);
	Display::logRectangle("Frame", this->Frame);
}

void	Display::configureMaximumSizes(void)
{
	int	monitor;
	int	width;
	int	height;

	monitor = GetCurrentMonitor();
	width = GetMonitorWidth(monitor) / 2;
	height = GetMonitorHeight(monitor) / 2;
	TraceLog(LOG_INFO, "Setting MaxWindow: %4ix%-4i", width, height);
	SetWindowMaxSize(width, height);
	
	TraceLog(LOG_DEBUG, "Monitor[%2.2i/%-2.2i] %4ix%-4i", monitor, GetMonitorCount(), GetMonitorWidth(monitor), GetMonitorHeight(monitor));
	TraceLog(LOG_DEBUG, "Screen        %4ix%-4i", monitor, GetScreenWidth(), GetScreenHeight());
	TraceLog(LOG_DEBUG, "Render        %4ix%-4i", monitor, GetRenderWidth(), GetRenderHeight());
}

void	Display::configureScreen(void)
{
	int	width = (int)this->HUD.width() + (int)this->Frame.width + this->margin * 3;
	int	height =(int)std::max(this->HUD.height(), this->Frame.height) + this->margin * 2;
	
	TraceLog(LOG_INFO, "Setting Window: %4ix%-4i", width, height);
	SetWindowSize(width, height);
	SetWindowPosition(DEFAULT_MARGIN, DEFAULT_MARGIN + 100);
}

void	Display::configureSizes(void)
{
	LOG_AS_TRACE();
	this->configureFrameSize();
	this->configureTileSize();
}

void	Display::configureFrameSize(void)
{
	LOG_AS_TRACE();
	this->Frame.width = (float)GetScreenWidth() - this->HUD.width() - 3 * (float)this->margin;
	this->Frame.height = GetScreenHeight() - 2 * (float)this->margin;
	Display::logRectangle("Frame", this->Frame);
}

void	Display::configureTileSize(void)
{
	LOG_AS_TRACE();
	this->tile.width = Frame.width / this->puzzle->getWidth();
	this->tile.height = Frame.height / this->puzzle->getHeight();
	Display::logRectangle("tile", this->tile);
}

bool	Display::setFontSize(const float size, bool updateSizes, bool includeHUD)
{
	if (size < 2 || size > 99)
	{
		TraceLog(LOG_ERROR, "Invalid font size of %.0f", size);
		return (false);
	}
	this->fontSize = size;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y;
	if (updateSizes)
		this->reconfigure();
	if (includeHUD)
		this->HUD.setFontsize(size, updateSizes);
	return (true);
}

bool	Display::setMargin(const int margin, bool updateSizes, bool includeHUD)
{
	if (margin < 0 || margin > 99)
	{
		TraceLog(LOG_ERROR, "Invalid margin size of %.0f", margin);
		return (false);
	}
	this->margin = margin;
	if (updateSizes)
		this->reconfigure();
	if (includeHUD)
		this->HUD.setMargin(margin, updateSizes);
	return (true);
}

void	Display::configurePositions(void)
{
	LOG_AS_TRACE();
	this->HUD.configurePositions();
	this->configureFramePosition();
}

void	Display::configureFramePosition(void)
{
	LOG_AS_TRACE();
	this->Frame.x = this->HUD.x() + this->HUD.width() + this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("Frame", this->Frame);
	this->tile.x = this->Frame.x;
	this->tile.y = this->Frame.y;
	Display::logRectangle("tile", this->tile);
}

void	Display::reconfigure(void)
{
	LOG_AS_TRACE();
	this->configureMinimumFrameSizes();
	this->configureMaximumSizes();
	this->configureSizes();
	this->configurePositions();
}

void	Display::logRectangle(const char* name, const Rectangle& rect)
{
	TraceLog(TraceLogLevel::LOG_INFO, "%-12s x %4.0f y %4.0f w %4.0f h %4.0f", name, rect.x, rect.y, rect.width, rect.height);
}

void	Display::renderScreen()
{
	// Background
	ClearBackground(Color{127, 63, 23, 255});
	// HUD
	this->HUD.render();
}

void	Display::renderTiles(nPuzzleState& state)
{
	Color	tileColor = {192, 192, 192, 255};
	int	xOffset = (this->tile.width - 20) / 2;
	int	yOffset = (this->tile.height - 20) / 2;

	DrawRectangleRec(this->Frame, Color{23, 23, 23, 255});
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
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

// Display	&Display::operator=(const Display &src)
// {
// 	if (this == &src)
// 		return (*this);

// 	return (*this);
// }
