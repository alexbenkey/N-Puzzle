/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayNPuzzle.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:48:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/09 18:57:37 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../assets/raylib/src/raylib.h"
#include "nPuzzle.hpp"
#include "Display.hpp"
#include "colors.hpp"

#include <iostream>

void	displayNPuzzle(nPuzzle* puzzle)
{
	SetTraceLogLevel(TraceLogLevel::LOG_TRACE);
	Display	graphics(puzzle);
	// graphics.setPuzzle(nullptr);

	try
	{
		while (!WindowShouldClose())
		{
			// Process user input
			switch (GetKeyPressed())
			{
				case KEY_RIGHT:	puzzle->moveRight();	break;
				case KEY_LEFT:	puzzle->moveLeft();	break;
				case KEY_DOWN:	puzzle->moveDown();	break;
				case KEY_UP:	puzzle->moveUp();	break;
				case KEY_T:	puzzle->printTarget();	break;
				case KEY_S:	puzzle->printPuzzle();	break;
				case KEY_R:
					if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
						TraceLog(LOG_WARNING, "Should reset to start now");
					else
						TraceLog(LOG_WARNING, "Press uppercase R to reset.");
					break;
				default:	break;
			}
			if (IsWindowResized())
				graphics.configureSizes();
			// Render Puzzle
			BeginDrawing();
			graphics.renderScreen();
			try
			{
				if (IsKeyDown(KEY_T))
					graphics.renderTargetState();
				else if (IsKeyDown(KEY_S))
					graphics.renderStartState();
				else
					graphics.renderCurrentState();
			}
			catch(const std::exception& e)
			{
				std::cerr	<< C_RED	<< "Error: "
							<< C_RESET	<< e.what()
							<< std::endl;
			}
			EndDrawing();
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
