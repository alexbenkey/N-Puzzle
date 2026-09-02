/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayNPuzzle.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:48:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/02 16:42:10 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raylib.h"
#include "nPuzzle.hpp"
#include "Display.hpp"
#include "colors.hpp"
#include "Errors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream

static void	ConfigureTrace(void);
static void	ProcessUserInput(int pressedKey, nPuzzle* puzzle, Display* display);
static void	ProcessUserInputShift(int pressedKey, nPuzzle* puzzle, Display* display);
static void	RenderFrame(Display& graphics);

void	displayNPuzzle(nPuzzle* puzzle)
{
	ConfigureTrace();
	Display	graphics(puzzle);

	try
	{
		while (!WindowShouldClose())
		{
			if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
				ProcessUserInputShift(GetKeyPressed(), puzzle, &graphics);
			else
				ProcessUserInput(GetKeyPressed(), puzzle, &graphics);
			if (IsWindowResized())
				graphics.configureSizes();
			RenderFrame(graphics);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr	<< C_RED	<< "Error: "
					<< C_RESET	<< e.what()
					<< std::endl;
	}
	CloseWindow();
}

static void	ConfigureTrace(void)
{
#if DEBUG == DEBUG_SILENT
	SetTraceLogLevel(TraceLogLevel::LOG_NONE);
#elif DEBUG <= DEBUG_ERROR
	SetTraceLogLevel(TraceLogLevel::LOG_ERROR);
#elif DEBUG <= DEBUG_WARNING
	SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
#elif DEBUG <= DEBUG_INFO
	SetTraceLogLevel(TraceLogLevel::LOG_INFO);
#elif DEBUG <= DEBUG_DEBUG
	SetTraceLogLevel(TraceLogLevel::LOG_DEBUG);
#elif DEBUG <= DEBUG_TRACE
	SetTraceLogLevel(TraceLogLevel::LOG_TRACE);
#elif DEBUG <= DEBUG_ALL
	SetTraceLogLevel(TraceLogLevel::LOG_ALL);
#endif
}

static void	ProcessUserInput(int pressedKey, nPuzzle* puzzle, Display* display)
{
	switch (pressedKey)
	{
		case KEY_RIGHT:	puzzle->moveRight();	break;
		case KEY_LEFT:	puzzle->moveLeft();	break;
		case KEY_DOWN:	puzzle->moveDown();	break;
		case KEY_UP:	puzzle->moveUp();	break;
		case KEY_SPACE:	puzzle->solveStep();	break;
		case KEY_ENTER:
		{
			display->resetSolutionAnimation();
			puzzle->solve();
		}
			break;
		default:	break;
	}
}

static void	ProcessUserInputShift(int pressedKey, nPuzzle* puzzle, Display* display)
{
	switch (pressedKey)
	{
#warning when changing search mode or heuristic while solution is playing either 'Segmentation fault (core dumped)' or 'vector::_M_range_check: __n (which is 1666318464) >= this->size() (which is 16)'
		case KEY_RIGHT:	puzzle->incrementSearchMode();	break;
		case KEY_LEFT:	puzzle->decrementSearchMode();	break;
		case KEY_DOWN:	puzzle->incrementHeuristicIndex();	break;
		case KEY_UP:	puzzle->decrementHeuristicIndex();	break;
		case KEY_R:
			display->resetSolutionAnimation();
			puzzle->resetToStart();
			break;
		case KEY_ENTER:
		{
			display->resetSolutionAnimation();
			puzzle->solve();
		}
			break;
		default:	break;
	}
}

static void	RenderFrame(Display& graphics)
{
	try
	{
		BeginDrawing();
		// render HUD
		graphics.renderHUD(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
		// render puzzle
		if (IsKeyDown(KEY_Q))
			graphics.renderAsQueueState();
		else if (IsKeyDown(KEY_S))
			graphics.renderAsStartState();
		else if (IsKeyDown(KEY_T))
			graphics.renderAsTargetState();
		else if (graphics.isPuzzleSolved())
			graphics.renderSolutionAnimation();
		else
		{
			graphics.resetSolutionAnimation();
			graphics.renderAsCurrentState();
		}
		EndDrawing();
	}
	catch(const std::exception& e)
	{
		std::cerr	<< C_RED	<< "Error: "
					<< C_RESET	<< e.what()
					<< std::endl;
	}
}
