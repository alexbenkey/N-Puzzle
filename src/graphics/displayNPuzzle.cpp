/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayNPuzzle.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:48:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/02 19:05:08 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../assets/raylib/src/raylib.h"
#include "nPuzzle.hpp"
#include "Display.hpp"
#include "colors.hpp"

// void	drawPuzzle(nPuzzle &puzzle);
// void	drawHUD(void);
#include <iostream>

void	displayNPuzzle(void)
{
	Display	graphics;

	nPuzzle	temp(5, 5);

	try
	{
		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(Color{23, 23, 23, 255});
			graphics.renderHUD();
			try
			{
				if (IsKeyDown(KEY_T))
					{}
				else if (IsKeyDown(KEY_S))
					{}
				else
					graphics.renderTiles();

				if (IsKeyPressed(KEY_T))
					temp.printTarget();
				if (IsKeyPressed(KEY_S))
					temp.printPuzzle();
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

// void	drawHUD(void)
// {
// 	DrawRectangle(0, 0, GetRenderWidth() / 5, GetRenderHeight(), ORANGE);
// 	DrawText("nPuzzle", 23, 20, 20, WHITE);
// 	DrawText("[S] display Start", 23, 40, 20, RED);
// 	DrawText("[T] display Target", 23, 60, 20, WHITE);
// }

// void	drawPuzzle(nPuzzle &puzzle)
// {
// 	if (IsKeyPressed(KEY_T))
// 		puzzle.printTarget();
// 	else if (IsKeyPressed(KEY_S))
// 		puzzle.printPuzzle();

// 	Rectangle	rect;
// 	rect.height = GetRenderHeight() / 5;
// 	rect.width = GetRenderWidth() / 5;
// 	rect.x = 0;
// 	rect.y = 0;
// 	DrawRectangleRec(rect, RED);
// 	rect.x += rect.width;
// 	DrawRectangleGradientEx(rect, RED, GREEN, BLUE, YELLOW);
// 	// rect.x += rect.width;
// 	// DrawRectangleRoundedLinesEx(rect, 1, 2, 2, RED);
// 	DrawRectangleLinesEx(rect, 2, Color{0,0,0,127});
// }

// // void	DrawTile(nPuzzleState::Tile& tile)
// // {
// // 	state.getTile()
// // }