/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayNPuzzle.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:48:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/30 18:18:54 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raylib.h"
#include "nPuzzle.hpp"
#include "Display.hpp"
#include "colors.hpp"
#include "Errors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream
#include <thread>	// std::thread

static void	ConfigureTrace(void);
static void	ProcessUserInput(int pressedKey, nPuzzle* puzzle);
static void	RenderFrame(Display& graphics);

void	displayNPuzzle(nPuzzle* puzzle)
{
	ConfigureTrace();
	Display	graphics(puzzle);

	try
	{
		while (!WindowShouldClose())
		{
			ProcessUserInput(GetKeyPressed(), puzzle);
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

static void	ProcessUserInput(int pressedKey, nPuzzle* puzzle)
{
	switch (pressedKey)
	{
		case KEY_RIGHT:
				puzzle->moveRight();
			break;
		case KEY_LEFT:
				puzzle->moveLeft();
			break;
		case KEY_DOWN:
			if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
				puzzle->incrementHeuristic();
			else
				puzzle->moveDown();
			break;
		case KEY_UP:
			if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
				puzzle->decrementHeuristic();
			else
				puzzle->moveUp();
			break;
		case KEY_T:	puzzle->printTarget();	break;
		case KEY_S:	puzzle->printPuzzle();	break;
		case KEY_Q:	puzzle->printQueue();	break;
		case KEY_R:
			if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
				puzzle->resetToStart();
			else
				TraceLog(LOG_WARNING, "Press uppercase R to reset.");
			break;
		case KEY_SPACE:
std::cerr	<< C_DGRAY	<< __FILE__	<<"::"	<< C_RESET	<< __func__	<< __LINE__	<< std::endl;
			puzzle->solveStep();
std::cerr	<< C_DGRAY	<< __FILE__	<<"::"	<< C_RESET	<< __func__	<< __LINE__	<< std::endl;
			break;
		case KEY_ENTER:
		{
			std::thread	solveThread(&nPuzzle::solve, puzzle);
			solveThread.detach();
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
		if (IsKeyDown(KEY_Q))
			graphics.renderAsQueueState();
		else if (IsKeyDown(KEY_S))
			graphics.renderAsStartState();
		else if (IsKeyDown(KEY_T))
			graphics.renderAsTargetState();
		else if (graphics.isPuzzleSolved())
			graphics.renderSolutionAnimation();
		else
			graphics.renderAsCurrentState();
		EndDrawing();
	}
	catch(const std::exception& e)
	{
		std::cerr	<< C_RED	<< "Error: "
					<< C_RESET	<< e.what()
					<< std::endl;
	}
}
