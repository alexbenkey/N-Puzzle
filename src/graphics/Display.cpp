/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:58:28 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/22 15:41:15 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>	// std::stream

std::unordered_map<char, std::string> Display::hotkeyList = {
	{ 'R', "Reset to Start" },
	{ 'Q', "Display Queue" },
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
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif

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
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DRED	<< "Deconstructor "
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

void	Display::setPuzzle(nPuzzle* puzzle)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->puzzle = puzzle;

	// Configuration of Areas
	this->configureMinimumSizes();
	this->configureMaximumSizes();
	this->configureScreen();
	this->configureSizes();
	this->configurePositions();
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureMinimumSizes(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE("Configuring Minimum sizes");
#elif DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "\tConfiguring Minimum sizes");
#endif
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
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->tile.width = (float)MeasureText("WW", this->fontSize) + 2 * this->margin;
	this->tile.height = this->fontSize + 2 * margin;
	Display::logRectangle("tile", this->tile);

	if (this->puzzle)
	{
		this->Frame.width = (float)this->puzzle->getWidth();
		this->Frame.height = (float)this->puzzle->getHeight();
	}
	else
	{
		this->Frame.width = 1;
		this->Frame.height = 1;
	}
	this->Frame.width = std::min(this->Frame.width * this->tile.width, 
								(float)GetMonitorWidth(GetCurrentMonitor()) - this->HUD.width());
	this->Frame.height = std::min(this->Frame.height * this->tile.height, 
								(float)GetMonitorHeight(GetCurrentMonitor()) - 2 * this->margin);
	Display::logRectangle("Frame", this->Frame);
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureMaximumSizes(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE("Configuring Maximum sizes");
#elif DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "\tConfiguring Maximum sizes");
#endif
	int	monitor;
	int	width;
	int	height;

	monitor = GetCurrentMonitor();
	width = GetMonitorWidth(monitor) / 2;
	height = GetMonitorHeight(monitor) / 2;
#if DEBUG >= DEBUG_DEBUG
	TraceLog(LOG_DEBUG, "Monitor[%2.2i/%-2.2i] %4ix%-4i", monitor, GetMonitorCount(), GetMonitorWidth(monitor), GetMonitorHeight(monitor));
	TraceLog(LOG_DEBUG, "Screen        %4ix%-4i", monitor, GetScreenWidth(), GetScreenHeight());
	TraceLog(LOG_DEBUG, "Render        %4ix%-4i", monitor, GetRenderWidth(), GetRenderHeight());
#endif
#if DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "Setting MaxWindow: %4ix%-4i", width, height);
#endif
	SetWindowMaxSize(width, height);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureScreen(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE("Configuring Screen Size");
#elif DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "\tConfiguring Screen Size");
#endif
	int	width = (int)this->HUD.width() + (int)this->Frame.width + this->margin * 3;
	int	height =(int)std::max(this->HUD.height(), this->Frame.height) + this->margin * 2;
	
	TraceLog(LOG_INFO, "Setting Window: %4ix%-4i", width, height);
	SetWindowSize(width, height);
	SetWindowPosition(DEFAULT_MARGIN, DEFAULT_MARGIN + 100);
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureSizes(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE("Configuring Frame and Tile Sizes");
#elif DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "\tConfiguring Frame and Tile sizes");
#endif
	this->configureFrameSize();
	this->configureTileSize();
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureFrameSize(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Frame.width = (float)GetScreenWidth() - this->HUD.width() - 3 * (float)this->margin;
	this->Frame.height = GetScreenHeight() - 2 * (float)this->margin;
	Display::logRectangle("Frame", this->Frame);
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureTileSize(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif

	if (this->puzzle)
	{
		this->tile.width = (float)this->puzzle->getWidth();
		this->tile.height = (float)this->puzzle->getHeight();
	}
	else
	{
		this->tile.width = 1;
		this->tile.height = 1;
	}
	this->tile.width = Frame.width / this->tile.width;
	this->tile.height = Frame.height / this->tile.height;
	Display::logRectangle("tile", this->tile);
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

bool	Display::setFontSize(const float size, bool updateSizes, bool includeHUD)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
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
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

bool	Display::setMargin(const int margin, bool updateSizes, bool includeHUD)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
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
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configurePositions(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE("Configuring Positions");
#elif DEBUG >= DEBUG_INFO
	TraceLog(LOG_INFO, "\tConfiguring Positions");
#endif
	this->HUD.configurePositions();
	this->configureFramePosition();
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::configureFramePosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Frame.x = this->HUD.x() + this->HUD.width() + this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("Frame", this->Frame);
	this->tile.x = this->Frame.x;
	this->tile.y = this->Frame.y;
	Display::logRectangle("tile", this->tile);
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::reconfigure(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->configureMinimumFrameSizes();
	this->configureMaximumSizes();
	this->configureSizes();
	this->configurePositions();
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::logRectangle(const char* name, const Rectangle& rect)
{
	TraceLog(TraceLogLevel::LOG_INFO, "%-12s x %4.0f y %4.0f w %4.0f h %4.0f", name, rect.x, rect.y, rect.width, rect.height);
}

void	Display::renderState(nPuzzleState* state)
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
	// Background
	ClearBackground(Color{127, 63, 23, 255});
	// HUD
	this->HUD.render(this->puzzle, state);
	this->renderTiles(*state);
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

void	Display::renderTiles(nPuzzleState& state)
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
	Color	tileColor = {192, 192, 192, 255};
	int	xOffset = (this->tile.width - 20) / 2;
	int	yOffset = (this->tile.height - 20) / 2;

	DrawRectangleRec(this->Frame, Color{23, 23, 23, 255});
	if (this->puzzle)
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

#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
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
