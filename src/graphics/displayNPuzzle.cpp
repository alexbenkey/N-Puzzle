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

// void	drawPuzzle(nPuzzle &puzzle);
// void	drawHUD(void);

void	displayNPuzzle(void)
{
	Display	graphics;

	nPuzzle	temp(5, 5);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{23, 23, 23, 255});
		graphics.render();
		EndDrawing();
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