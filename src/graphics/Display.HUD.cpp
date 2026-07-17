/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:44:29 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/14 18:39:32 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

Display::HUD::HUD(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif

	this->setMargin(DEFAULT_MARGIN, false);
	this->setFontsize(DEFAULT_FONTSIZE, false);
	this->configureSizes(false);
	this->configurePositions();
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

Display::HUD::~HUD(void)
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

void	Display::HUD::setMargin(const int& margin, bool updateSizes)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->margin = margin;
	if (updateSizes)
		this->configureSizes();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::setFontsize(const float& fontSize, bool updateSizes)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->fontSize = fontSize;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y;
	if (!this->fontHeight)
		this->fontHeight = this->fontSize;
	if (updateSizes)
		this->configureSizes();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureSizes(bool updatePositions)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->configureDataSize(false);
	this->configureHeuristicsSize(false);
	this->configureControlSize(false);
	this->configureMovementSize(false);
	this->configureFrameSize(updatePositions);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureDataSize(bool updateFrame)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Data.width = MeasureText("  [M]anhattan: 00", this->fontSize);
	this->Data.height = 3 * this->fontHeight;
	Display::logRectangle("HUD.Data", this->Data);
	if (updateFrame)
		this->configureFrameSize();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureHeuristicsSize(bool updateFrame)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Heuristics.height = (heuristic::size + 1) * this->fontHeight;
	for (size_t line = 0; line < heuristic::size; ++line)
	{
		float	width = (float)MeasureText(TextFormat("[0] %s: 000", heuristic::function[line].name), this->fontSize);
		if (width > this->Heuristics.width)
			this->Heuristics.width = width;
	}
	Display::logRectangle("HUD.Heuristics", this->Heuristics);
	if (updateFrame)
		this->configureFrameSize();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureControlSize(bool updateFrame)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Controls.width = 0;
	for (const auto& key : Display::hotkeyList)
	{
		const char* buffer = TextFormat("[%c] %s", key.first, key.second.c_str());
		this->Controls.width = std::max(this->Controls.width, (float)MeasureText(buffer, this->fontSize));
	}
	this->Controls.height = (float)Display::hotkeyList.size() * this->fontHeight;
	Display::logRectangle("HUD.Controls", this->Controls);
	if (updateFrame)
		this->configureFrameSize();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureMovementSize(bool updateFrame)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Movement.width = this->margin * 5;
	this->Movement.height = this->Movement.width;
	Display::logRectangle("HUD.Movement", this->Movement);
	if (updateFrame)
		this->configureFrameSize();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureFrameSize(bool updatePositions)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Frame.width = 0;
	this->Frame.height = (float)this->margin;
	for (const Rectangle& rect : { this->Data, this->Heuristics, this->Controls, this->Movement })
	{
		this->Frame.width = std::max(this->Frame.width, rect.width);
		this->Frame.height += rect.height + this->margin;
	}
	this->Frame.width += 2 * (float)this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);
	if (updatePositions)
		this->configurePositions();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configurePositions(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->configureFramePosition();
	this->configureDataPosition();
	this->configureHeuristicsPosition();
	this->configureControlsPosition();
	this->configureMovementPosition();

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureFramePosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Frame.x = this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureDataPosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Data.x = this->Frame.x + this->margin;
	this->Data.y = this->Frame.y + this->margin;
	Display::logRectangle("HUD.Data", this->Data);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureHeuristicsPosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Heuristics.x = this->Frame.x + this->margin;
	this->Heuristics.y = this->Data.y + this->Data.height + this->margin;
	Display::logRectangle("HUD.Heuristics", this->Data);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureControlsPosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Controls.x = this->Frame.x + this->margin;
	this->Controls.y = this->Heuristics.y + this->Heuristics.height + this->margin;
	Display::logRectangle("HUD.Controls", this->Controls);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::configureMovementPosition(void)
{
#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
	this->Movement.x = this->Frame.x + (this->Frame.width - this->Movement.width) / 2;
	this->Movement.y = this->Controls.y + this->Controls.height + this->margin;
	Display::logRectangle("HUD.Movement", this->Movement);

#if DEBUG >= DEBUG_TRACE
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::render(nPuzzle* puzzle) const
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
	this->renderFrame();
	this->renderData(puzzle);
	this->renderHeuristics(puzzle);
	this->renderControls();
	this->renderMovement();

#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::renderFrame(void) const
{
	DrawRectangleRec(this->Frame, Color{23,23,23,255});

#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::renderData(nPuzzle* puzzle) const
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Data, 1, Color{255,23,23,255});
#endif
	const char*	buffer;

	for (size_t i = 0; ; i++)
	{
		switch (i)
		{
			case 0:
				if (puzzle)
					buffer = TextFormat("Size: %ix%i", puzzle->getWidth(), puzzle->getHeight());
				else
					buffer = TextFormat("Size: %ix%i", 0, 0);
				break;
			case 1:
				buffer = TextFormat("Solvbility");
				break;
			case 2:
				buffer = TextFormat("Moves: %i", 0);
				break;
			default:
				goto endLoop;
		}
		DrawText(buffer, this->Data.x, this->Data.y + i * this->fontHeight, this->fontSize, WHITE);
	}
	endLoop:
	return;

#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::renderHeuristics(nPuzzle* puzzle) const
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Heuristics, 1, Color{255,23,23,255});
#endif
	const char* buffer;

	DrawText("Heuristics", this->Heuristics.x, this->Heuristics.y, this->fontSize, RED);
	for (size_t line = 0; line < heuristic::size; ++line)
	{
		buffer = TextFormat("[%i] %s: %i", line, heuristic::function[line].name, heuristic::function[line].f(&puzzle->getCurrentState(), &puzzle->getTargetState()));
		DrawText(buffer, this->Heuristics.x, this->Heuristics.y + (line + 1) * this->fontHeight, this->fontSize, WHITE);
	}
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

void	Display::HUD::renderControls(void) const
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Controls, 1, Color{23,255,23,255});
#endif
	const char*	buffer;
	size_t		i;
	i = 0;
	for (auto it = Display::hotkeyList.begin(); it != Display::hotkeyList.end(); ++it, ++i)
	{
		buffer = TextFormat("[%c] %s", it->first, it->second.c_str());
		DrawText(buffer, this->Controls.x, this->Controls.y + i * this->fontHeight, this->fontSize, WHITE);
	}
}

void	Display::HUD::renderMovement(void) const
{
#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Movement, 1, Color{23,23,255,255});
#endif
	int	length;
	int width;

	length = std::min(this->Movement.width, this->Movement.height);
	width = length / 3;
	DrawRectangle(this->Movement.x, this->Movement.y + (length - width) / 2, length, width, Color{192,192,192,255});
	DrawRectangle(this->Movement.x + (length - width) / 2, this->Movement.y, width, length, Color{192,192,192,255});

#if DEBUG >= DEBUG_ALL
	LOG_AS_TRACE();
#endif
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
