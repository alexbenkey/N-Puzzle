/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:44:29 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/31 14:03:40 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.HUD.hpp"
#include "colors.hpp"
#include "heuristic.hpp"
#include "nPuzzle.State.hpp"
#include "Errors.hpp"

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
TRACE_POSITION();
	this->margin = margin;
	if (updateSizes)
		this->configureSizes();

TRACE_POSITION();
}

void	Display::HUD::setFontsize(const float& fontSize, bool updateSizes)
{
TRACE_POSITION();
	this->fontSize = fontSize;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y;
	if (!this->fontHeight)
		this->fontHeight = this->fontSize;
	if (updateSizes)
		this->configureSizes();

TRACE_POSITION();
}

void	Display::HUD::configureSizes(bool updatePositions)
{
TRACE_POSITION();
	this->configureDataSize(false);
	this->configureHeuristicsSize(false);
	this->configureControlSize(false);
	this->configureMovementSize(false);
	this->configureSolverSize(false);	// later cause variable width
	this->configureFrameSize(updatePositions);

TRACE_POSITION();
}

void	Display::HUD::configureDataSize(bool updateFrame)
{
TRACE_POSITION();
	this->Data.width = MeasureText("  [M]anhattan: 00", this->fontSize);
	this->Data.height = 4 * this->fontHeight;
	Display::logRectangle("HUD.Data", this->Data);
	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureSolverSize(bool updateFrame)
{
TRACE_POSITION();
	this->Solver.width = 0;
	for (const Rectangle& rect : { this->Data, this->Heuristics, this->Controls, this->Movement })
	{
		this->Solver.width = std::max(this->Solver.width, rect.width);
	}
	this->Solver.height = 3 * this->fontHeight;
	Display::logRectangle("HUD.Solver", this->Solver);
	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureHeuristicsSize(bool updateFrame)
{
TRACE_POSITION();
	this->Heuristics.height = (heuristic::size + 2) * this->fontHeight;
	for (int32_t line = 0; line < heuristic::size; ++line)
	{
		float	width = (float)MeasureText(TextFormat("[0] %s: 000", heuristic::function[line].name), this->fontSize);
		if (width > this->Heuristics.width)
			this->Heuristics.width = width;
	}
	Display::logRectangle("HUD.Heuristics", this->Heuristics);
	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureControlSize(bool updateFrame)
{
TRACE_POSITION();
	this->Controls.width = 0;
	for (const auto& key : Display::hotkeyList)
	{
		const char* buffer = TextFormat("[%c] %s", key.first, key.second.c_str());
		this->Controls.width = std::max(this->Controls.width, (float)MeasureText(buffer, this->fontSize));
	}
	this->Controls.height = ((float)Display::hotkeyList.size() + 1) * this->fontHeight;
	Display::logRectangle("HUD.Controls", this->Controls);
	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureMovementSize(bool updateFrame)
{
TRACE_POSITION();
	this->Movement.width = this->margin * 5;
	this->Movement.height = this->Movement.width;
	Display::logRectangle("HUD.Movement", this->Movement);
	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureFrameSize(bool updatePositions)
{
TRACE_POSITION();
	this->Frame.width = 0;
	this->Frame.height = (float)this->margin;
	for (const Rectangle& rect : { this->Data, this->Solver, this->Heuristics, this->Controls, this->Movement })
	{
		this->Frame.width = std::max(this->Frame.width, rect.width);
		this->Frame.height += rect.height + this->margin;
	}
	this->Frame.width += 2 * (float)this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);
	if (updatePositions)
		this->configurePositions();

TRACE_POSITION();
}

void	Display::HUD::configurePositions(void)
{
TRACE_POSITION();
	this->configureFramePosition();
	this->configureDataPosition();
	this->configureSolverPosition();
	this->configureHeuristicsPosition();
	this->configureControlsPosition();
	this->configureMovementPosition();

TRACE_POSITION();
}

void	Display::HUD::configureFramePosition(void)
{
TRACE_POSITION();
	this->Frame.x = this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);

TRACE_POSITION();
}

void	Display::HUD::configureDataPosition(void)
{
TRACE_POSITION();
	this->Data.x = this->Frame.x + this->margin;
	this->Data.y = this->Frame.y + this->margin;
	Display::logRectangle("HUD.Data", this->Data);

TRACE_POSITION();
}

void	Display::HUD::configureSolverPosition(void)
{
TRACE_POSITION();
	this->Solver.x = this->Frame.x + this->margin;
	this->Solver.y = this->Data.y + this->Data.height + this->margin;
	Display::logRectangle("HUD.Solver", this->Solver);

TRACE_POSITION();
}

void	Display::HUD::configureHeuristicsPosition(void)
{
TRACE_POSITION();
	this->Heuristics.x = this->Frame.x + this->margin;
	this->Heuristics.y = this->Solver.y + this->Solver.height + this->margin;
	Display::logRectangle("HUD.Heuristics", this->Heuristics);

TRACE_POSITION();
}

void	Display::HUD::configureControlsPosition(void)
{
TRACE_POSITION();
	this->Controls.x = this->Frame.x + this->margin;
	this->Controls.y = this->Heuristics.y + this->Heuristics.height + this->margin;
	Display::logRectangle("HUD.Controls", this->Controls);

TRACE_POSITION();
}

void	Display::HUD::configureMovementPosition(void)
{
TRACE_POSITION();
	this->Movement.x = this->Frame.x + (this->Frame.width - this->Movement.width) / 2;
	this->Movement.y = this->Controls.y + this->Controls.height + this->margin;
	Display::logRectangle("HUD.Movement", this->Movement);

TRACE_POSITION();
}

void	Display::HUD::render(nPuzzle* puzzle, nPuzzle::State* state) const
{
TRACE_POSITION();
	this->renderFrame();
	this->renderData(puzzle, state);
	this->renderSolver(puzzle);
	this->renderHeuristics(state, puzzle->getHeuristicIndex());
	this->renderControls();
	this->renderMovement();

TRACE_POSITION();
}

void	Display::HUD::renderFrame(void) const
{
	DrawRectangleRec(this->Frame, Color{23,23,23,255});

TRACE_POSITION();
}

void	Display::HUD::renderData(nPuzzle* puzzle, nPuzzle::State* state) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Data, 1, Color{255,23,23,255});
#endif
	const char*		buffer;
	static int32_t	oldPercentage = 0;

	DrawText("nPuzzle", this->Data.x, this->Data.y, this->fontSize, RED);
	for (size_t i = 1; ; i++)
	{
		switch (i)
		{
			case 1:
				if (puzzle)
					buffer = TextFormat("Size: %ix%i", puzzle->getWidth(), puzzle->getHeight());
				else
					buffer = TextFormat("Size: %ix%i", 0, 0);
				break;
			case 2:
				buffer = TextFormat("Solvbility: ???");
				break;
			case 3:
				if (state)
					buffer = TextFormat("Moves: %i", state->getCost());
				else
					buffer = TextFormat("Moves: N/A");
				break;
			default:
				goto endLoop;
		}
		DrawText(buffer, this->Data.x, this->Data.y + i * this->fontHeight, this->fontSize, WHITE);
	}
	endLoop:
	return;

TRACE_POSITION();
}

void	Display::HUD::renderSolver(nPuzzle* puzzle) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Solver, 1, Color{255,23,23,255});
#endif
	const char*	buffer;
	int32_t	posY;

	// Header
	{
		posY = this->Solver.y;
		buffer = TextFormat("Solver");
		DrawText(buffer, this->Solver.x, posY, this->fontSize, RED);
	}
	// Queue
	{
		posY = this->Solver.y + this->fontHeight;
		buffer = TextFormat("Queue: %7i", puzzle->getQueueSize());
		DrawText(buffer, this->Solver.x, posY, this->fontSize, WHITE);
	}
	// Progress
	{
		posY = this->Solver.y + this->fontHeight * 2;
		static int32_t	oldPercentage = 0;
		int32_t	h = puzzle->getBestSolverHeuristic();
		int32_t g = puzzle->getQueueState().getCost();
		int32_t	percentage = (g * 100) / (g + h);
		if (percentage < oldPercentage)
			--oldPercentage;
		else
			oldPercentage = percentage;

		DrawRectangle(this->Solver.x, posY, this->Solver.width * oldPercentage / 100, this->fontHeight, GRAY);
		DrawRectangle(this->Solver.x, posY, this->Solver.width * percentage / 100, this->fontHeight, WHITE);
		DrawRectangleLines(this->Solver.x, posY, this->Solver.width, this->fontHeight, WHITE);

		int32_t	adjustX = MeasureText("G: 000",this->fontSize) / 2;
		buffer = TextFormat("G: %3i", g);
		DrawText(buffer, this->Solver.x + this->Solver.width / 3 - adjustX, posY, this->fontSize, ORANGE);
		buffer = TextFormat("H: %3i", h);
		DrawText(buffer, this->Solver.x + this->Solver.width * 2 / 3 - adjustX, posY, this->fontSize, ORANGE);
	}
}

void	Display::HUD::renderHeuristics(nPuzzle::State* state, int32_t h) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Heuristics, 1, Color{255,23,23,255});
#endif
	const char* buffer;
	Color	selected{255, 127, 0, 255};
	Color	unselected = WHITE;

	DrawText("Heuristics", this->Heuristics.x, this->Heuristics.y, this->fontSize, RED);
	for (int32_t line = 0; line < heuristic::size; ++line)
	{
		buffer = TextFormat("%s: %i", heuristic::function[line].name, state->getHeuristic(line));
		DrawText(buffer, this->Heuristics.x, this->Heuristics.y + (line + 1) * this->fontHeight, this->fontSize, (line == h) ? selected : unselected);
	}
	DrawText("[SHIFT] + [^]/[v]", this->Heuristics.x, this->Heuristics.y + (heuristic::size + 1) * this->fontHeight, this->fontSize, WHITE);
TRACE_POSITION();
}

void	Display::HUD::renderControls(void) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Controls, 1, Color{23,255,23,255});
#endif
	DrawText("Controls", this->Controls.x, this->Controls.y, this->fontSize, RED);

	const char*	buffer;
	size_t	i = 1;
	for (auto it = Display::hotkeyList.begin(); it != Display::hotkeyList.end(); ++it, ++i)
	{
		buffer = TextFormat("[%c] %s", it->first, it->second.c_str());
		DrawText(buffer, this->Controls.x, this->Controls.y + i * this->fontHeight, this->fontSize, WHITE);
	}
}

void	Display::HUD::renderMovement(void) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Movement, 1, Color{23,23,255,255});
#endif
	int	length;
	int width;

	length = std::min(this->Movement.width, this->Movement.height);
	width = length / 3;
	DrawRectangle(this->Movement.x, this->Movement.y + (length - width) / 2, length, width, Color{192,192,192,255});
	DrawRectangle(this->Movement.x + (length - width) / 2, this->Movement.y, width, length, Color{192,192,192,255});

TRACE_POSITION();
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
