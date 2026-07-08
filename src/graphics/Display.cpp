/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:58:28 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/08 20:05:31 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>
// std::

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
				<< C_GREEN	<< "Display"
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
	SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1, 1, "nPuzzle");
	// this->setFontSize(DEFAULT_FONTSIZE);
	this->fontSize = DEFAULT_FONTSIZE;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "W", this->fontSize, 0).y;
	// this->setMargin(DEFAULT_MARGIN);
	this->margin = DEFAULT_MARGIN;
	this->configureMinimumSizes();
	this->configureMaximumSizes();
	this->configureSizes();
	SetWindowPosition(DEFAULT_MARGIN, DEFAULT_MARGIN);
	SetWindowSize(this->HUD.Frame.width + this->Frame.width + this->margin * 3, std::max(this->HUD.Frame.height, this->Frame.height) + this->margin * 2);
	this->configurePositions();

	// SetWindowSize(this->HUD.Frame.width + this->Frame.width + 3 * this->margin, this->Frame.height + 2 * this->margin);

	// this->setFontSize(DEFAULT_FONTSIZE);
	// this->setMargin(DEFAULT_MARGIN);
	// SetWindowMinSize(800, 450);
	// SetWindowSize(800, 450);
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

void	Display::configureMinimumSizes(void)
{
	this->configureHUDDataSize();
	this->configureHUDControlSize();
	this->configureHUDMovementSize();
	this->configureHUDFrameSize();
	this->configureMinimumFrameSizes();
	SetWindowMinSize(this->HUD.Frame.width + this->Frame.width + this->margin * 3, 
		std::max(this->HUD.Frame.height, this->Frame.height) + this->margin * 2);
}

void	Display::configureHUDDataSize(void)
{
	this->HUD.Data.width = MeasureText("  [M]anhattan: 00", this->fontSize);
	this->HUD.Data.height = 7 * this->fontHeight;
	Display::logRectangle("HUD.Data", this->HUD.Data);
}

void	Display::configureHUDControlSize()
{
	this->HUD.Controls.width = 0;
	for (const auto& key : Display::hotkeyList)
	{
		const char* buffer = TextFormat("[%c] %s", key.first, key.second.c_str());
		this->HUD.Controls.width = std::max(this->HUD.Controls.width, (float)MeasureText(buffer, this->fontSize));
	}
	this->HUD.Controls.height = (float)Display::hotkeyList.size() * this->fontHeight;
	Display::logRectangle("HUD.Controls", this->HUD.Controls);
}

void	Display::configureHUDMovementSize(void)
{
	this->HUD.Movement.width = this->margin * 5;
	this->HUD.Movement.height = this->HUD.Movement.width;
	Display::logRectangle("HUD.Movement", this->HUD.Movement);
}

void	Display::configureMinimumFrameSizes()
{
	this->tile.width = (float)MeasureText("WW", this->fontSize) + 2 * this->margin;
	this->tile.height = this->fontSize + 2 * margin;
	Display::logRectangle("tile", this->tile);

	this->Frame.width = this->tile.width * (float)this->puzzle->getWidth();
	this->Frame.width = std::min(this->Frame.width, (float)GetMonitorWidth(GetCurrentMonitor()) - this->HUD.Frame.width);
	this->Frame.height = this->tile.height * this->puzzle->getHeight();
	this->Frame.height = std::min(this->Frame.height, (float)GetMonitorHeight(GetCurrentMonitor()) - 2 * this->margin);
	Display::logRectangle("Frame", this->Frame);
}

void	Display::configureHUDFrameSize(void)
{
	this->HUD.Frame.width = 0;
	this->HUD.Frame.height = (float)this->margin;
	for (const Rectangle& rect : { this->HUD.Data, this->HUD.Controls, this->HUD.Movement })
	{
		this->HUD.Frame.width = std::max(this->HUD.Frame.width, rect.width);
		this->HUD.Frame.height += rect.height + this->margin;
	}
	this->HUD.Frame.width += 2 * (float)this->margin;
	Display::logRectangle("HUD.Frame", this->HUD.Frame);
}

void	Display::configureMaximumSizes(void)
{
	int	monitor;

	monitor = GetCurrentMonitor();
	SetWindowMaxSize(GetMonitorWidth(monitor) / 2, GetMonitorHeight(monitor) / 2);
	
	TraceLog(LOG_DEBUG, "%s[%i] Render %i", __func__, __LINE__, GetRenderHeight());
	TraceLog(LOG_DEBUG, "%s[%i] Screen %i", __func__, __LINE__, GetScreenHeight());
	TraceLog(LOG_DEBUG, "%s[%i] Monitor %i", __func__, __LINE__, GetMonitorHeight(monitor));
	TraceLog(LOG_DEBUG, "%s[%i] MonitorP %i", __func__, __LINE__, GetMonitorPhysicalHeight(monitor));
}

void	Display::configureSizes(void)
{
	this->configureFrameSize();
	this->configureTileSize();
}

void	Display::configureFrameSize(void)
{
	this->Frame.width = (float)GetRenderWidth() - this->HUD.Frame.width - 3 * this->margin;
	this->Frame.height = GetRenderHeight() - 2 * this->margin;
	Display::logRectangle("Frame", this->Frame);
}

void	Display::configureTileSize(void)
{
	this->tile.width = Frame.width / this->puzzle->getWidth();
	this->tile.height = Frame.height / this->puzzle->getHeight();
	Display::logRectangle("tile", this->tile);
}

bool	Display::setFontSize(const float size)
{
	if (size < 2 || size > 99)
	{
		TraceLog(LOG_ERROR, "Invalid font size of %.0f", size);
		return (false);
	}
	this->fontSize = size;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y;
	this->reconfigure();
	return (true);
}

bool	Display::setMargin(const int margin)
{
	if (margin < 0 || margin > 99)
	{
		TraceLog(LOG_ERROR, "Invalid margin size of %.0f", margin);
		return (false);
	}
	this->margin = margin;
	this->reconfigure();
	return (true);
}

void	Display::configurePositions(void)
{
	this->configureHUDFramePosition();
	this->configureHUDDataPosition();
	this->configureHUDControlsPosition();
	this->configureHUDMovementPosition();
	this->configureFramePosition();
}
void	Display::configureHUDFramePosition(void)
{
	this->HUD.Frame.x = this->margin;
	this->HUD.Frame.y = this->margin;
	Display::logRectangle("HUD.Frame", this->HUD.Frame);
}
void	Display::configureHUDDataPosition(void)
{
	this->HUD.Data.x = this->HUD.Frame.x + this->margin;
	this->HUD.Data.y = this->HUD.Frame.y + this->margin;
	Display::logRectangle("HUD.Data", this->HUD.Data);
}
void	Display::configureHUDControlsPosition(void)
{
	this->HUD.Controls.x = this->HUD.Frame.x + this->margin;
	this->HUD.Controls.y = this->HUD.Data.y + this->HUD.Data.height + this->margin;
	Display::logRectangle("HUD.Controls", this->HUD.Controls);
}
void	Display::configureHUDMovementPosition(void)
{
	this->HUD.Movement.x = this->HUD.Frame.x + (this->HUD.Frame.width - this->HUD.Movement.width) / 2;
	this->HUD.Movement.y = this->HUD.Controls.y + this->HUD.Controls.height + this->margin;
	Display::logRectangle("HUD.Movement", this->HUD.Movement);
}
void	Display::configureFramePosition(void)
{
	this->Frame.x = this->HUD.Frame.x + this->HUD.Frame.width + this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("Frame", this->Frame);
	this->tile.x = this->Frame.x;
	this->tile.y = this->Frame.y;
	Display::logRectangle("tile", this->tile);
}

void	Display::reconfigure(void)
{
	this->configureMinimumFrameSizes();
	this->configureMaximumSizes();
	this->configureSizes();
	this->configurePositions();
}

void	Display::logRectangle(const char* name, const Rectangle& rect)
{
	TraceLog(LOG_DEBUG, "%-12s x %4.0f y %4.0f w %4.0f h %4.0f", name, rect.x, rect.y, rect.width, rect.height);
}

void	Display::renderScreen()
{
	// Background
	ClearBackground(Color{127, 63, 23, 255});
	// HUD
	DrawRectangleRec(this->HUD.Frame, Color{23, 23, 23, 255});
	this->renderHUDData();
	this->renderHUDControls();
	this->renderHUDMovement();
}
void	Display::renderHUDData()
{
	const char*	buffer;

	// DrawRectangleLinesEx(this->HUD.Data, 1, Color{255,23,23,255});
	for (size_t i = 0; ; i++)
	{
		switch (i)
		{
			case 0:
				buffer = TextFormat("Size: %ix%i", this->puzzle->getWidth(), this->puzzle->getHeight());
				break;
			case 1:
				buffer = TextFormat("Solvbility");
				break;
			case 2:
				buffer = TextFormat("Moves: %i", 0);
				break;
			case 3:
				buffer = TextFormat("Heuristics");
				break;
			case 4:
				buffer = TextFormat("  [M]anhattan: %i", 0);
				break;
			default:
				goto endLoop;
		}
		DrawText(buffer, this->HUD.Data.x, this->HUD.Data.y + i * this->fontHeight, this->fontSize, WHITE);
	}
	endLoop:
	return;
}

void	Display::renderHUDControls()
{
	const char*	buffer;
	size_t		i;

	// DrawRectangleLinesEx(this->HUD.Controls, 1, Color{23,255,23,255});
	i = 0;
	for (auto it = Display::hotkeyList.begin(); it != Display::hotkeyList.end(); ++it, ++i)
	{
		buffer = TextFormat("[%c] %s", it->first, it->second.c_str());
		DrawText(buffer, this->HUD.Controls.x, this->HUD.Controls.y + i * this->fontHeight, this->fontSize, WHITE);
	}
}

void	Display::renderHUDMovement()
{
	int	length;
	int width;

	// DrawRectangleLinesEx(this->HUD.Movement, 1, Color{23,23,255,255});
	length = std::min(this->HUD.Movement.width, this->HUD.Movement.height);
	width = length / 3;
	DrawRectangle(this->HUD.Movement.x, this->HUD.Movement.y + (length - width) / 2, length, width, Color{192,192,192,255});
	DrawRectangle(this->HUD.Movement.x + (length - width) / 2, this->HUD.Movement.y, width, length, Color{192,192,192,255});
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

Display	&Display::operator=(const Display &src)
{
	if (this == &src)
		return (*this);

	return (*this);
}
