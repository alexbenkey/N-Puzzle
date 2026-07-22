/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayNPuzzle.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:48:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/22 18:49:28 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../assets/raylib/src/raylib.h"
#include "nPuzzle.hpp"
#include "displayNPuzzle.hpp"
#include "Display.hpp"
#include "colors.hpp"
#include "Errors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream

void	displayNPuzzle(nPuzzle* puzzle)
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
	Display	graphics(puzzle);
	int32_t hVal = 1; 

	try
	{
		while (!WindowShouldClose())
		{
			// Process user input
			int	pressedKey = GetKeyPressed();
			
			switch (pressedKey)
			{
				case KEY_RIGHT:
					if (IsKeyDown(KEY_Q))
						puzzle->incrementQueue();
					else
						puzzle->moveRight(), puzzle->clearStates();
					break;
				case KEY_LEFT:
					if (IsKeyDown(KEY_Q))
						puzzle->decrementQueue();
					else
						puzzle->moveLeft(), puzzle->clearStates();
					break;
				case KEY_DOWN:	puzzle->moveDown(), puzzle->clearStates();	break;
				case KEY_UP:	puzzle->moveUp(), puzzle->clearStates();	break;
				case KEY_T:	puzzle->printTarget();	break;
				case KEY_S:	puzzle->printPuzzle();	break;
				case KEY_R:
					if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
						puzzle->resetStates();
					else
						TraceLog(LOG_WARNING, "Press uppercase R to reset.");
					break;
				case KEY_SPACE:
					puzzle->solveStep(hVal);
					break;
				case KEY_ZERO ... KEY_NINE:
					{
						const int32_t requested = pressedKey - KEY_ZERO;

						if (requested >= 0 && requested < heuristic::size)
						{
							hVal = requested;
							puzzle->clearStates();

							TraceLog(
								LOG_INFO,
								"selected heuristid %i: %s",
								hVal,
								heuristic::function[hVal].name
							);
						}
						else
							TraceLog(LOG_WARNING, "invalid heuristic: %i", requested);
					}
					break ;
				case KEY_ENTER:
					puzzle->solve(hVal);
					break;
				default:	break;
			}
			// Check for resize
			if (IsWindowResized())
				graphics.configureSizes();
			// Render frame
			try
			{
				BeginDrawing();
				if (IsKeyDown(KEY_Q))
					graphics.renderAsQueueState();
				else if (IsKeyDown(KEY_S))
					graphics.renderAsStartState();
				else if (IsKeyDown(KEY_T))
					graphics.renderAsTargetState();
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
	}
	catch(const std::exception& e)
	{
		std::cerr	<< C_RED	<< "Error: "
					<< C_RESET	<< e.what()
					<< std::endl;
	}
	CloseWindow();
}
