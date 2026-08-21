/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:44:29 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/21 19:16:09 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.HUD.hpp"
#include "colors.hpp"
#include "heuristic.hpp"
#include "nPuzzle.State.hpp"
#include "Errors.hpp"

#include <iostream>	// std::stream

std::vector<std::pair<const char*, const char*> > Display::HUD::hotkeyList = {
	{ "s", "Display Start" },
	{ "t", "Display Target" },
	{ "q", "Display Queue" },
	{ "SPACE", "Solve step" },
	{ "ENTER", "Solve" },
	{ "SHIFT", "More options..." },
};

std::vector<std::pair<const char*, const char*> > Display::HUD::hotkeyListAlternative = {
	{ "S", "Display Start" },
	{ "T", "Display Target" },
	{ "Q", "Display Queue" },
	{ "R", "Reset to Start" },
	{ "SPACE", "Solve step" },
	{ "ENTER", "Solve" },
};

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
	this->Data.Left.width = MeasureText("Solvability:", this->fontSize);
	this->Data.Left.height = this->fontHeight * 3;
	Display::logRectangle("HUD.Data.Left", this->Data.Left);

	this->Data.Right.width = MeasureText("Unsolvable", this->fontSize);
	this->Data.Right.height = this->Data.Left.height;
	Display::logRectangle("HUD.Data.Right", this->Data.Right);

	this->Data.Frame.width = this->Data.Left.width + this->Data.Right.width + (float)this->margin;
	this->Data.Frame.height = std::max(this->Data.Left.height, this->Data.Right.height) + this->fontHeight;

	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureSolverSize(bool updateFrame)
{
TRACE_POSITION();
	this->Solver.Left.width = (float)MeasureText("Queue:", this->fontSize);
	this->Solver.Left.height = this->fontHeight * 2;
	Display::logRectangle("HUD.Solver.Left", this->Solver.Left);

	this->Solver.Right.width = (float)MeasureText("Uniform-cost", this->fontSize);
	this->Solver.Right.height = this->Solver.Left.height;
	Display::logRectangle("HUD.Solver.Right", this->Solver.Right);

	this->Solver.Frame.width = this->Solver.Left.width + this->Solver.Right.width + this->margin;
	for (const Rectangle& rect : { this->Data.Frame, this->Heuristics.Frame, this->Controls.Frame, this->Movement })
		this->Solver.Frame.width = std::max(this->Solver.Frame.width, rect.width);
	this->Solver.Frame.height = this->Solver.Left.height + this->fontHeight * 3;
	Display::logRectangle("HUD.Solver.Frame", this->Solver.Frame);

	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureHeuristicsSize(bool updateFrame)
{
TRACE_POSITION();
	this->Heuristics.Left.height = heuristic::size * this->fontHeight;
	this->Heuristics.Right.height = this->Heuristics.Left.height;
	this->Heuristics.Frame.height = this->Heuristics.Left.height + 2 * this->fontHeight;

	this->Heuristics.Left.width = 0;
	for (int32_t line = 0; line < heuristic::size; ++line)
	{
		this->Heuristics.Left.width = std::max(this->Heuristics.Left.width, (float)MeasureText(heuristic::function[line].name, this->fontSize));
	}
	this->Heuristics.Right.width = (float)MeasureText("0000", this->fontSize);
	this->Heuristics.Frame.width = std::max(this->Heuristics.Left.width + this->Heuristics.Right.width + this->margin, 
											this->fontHeight * 2 + (float)MeasureText(" Change heuristic", this->fontSize));
	Display::logRectangle("HUD.Heuristics.Frame", this->Heuristics.Frame);
	Display::logRectangle("HUD.Heuristics.Left", this->Heuristics.Left);
	Display::logRectangle("HUD.Heuristics.Right", this->Heuristics.Right);

	if (updateFrame)
		this->configureFrameSize();

TRACE_POSITION();
}

void	Display::HUD::configureControlSize(bool updateFrame)
{
TRACE_POSITION();
	this->Controls.Left.width = 0;
	this->Controls.Right.width = 0;
	for (const auto& list: {Display::HUD::hotkeyList, Display::HUD::hotkeyListAlternative})
	{
		for (const auto& key: list)
		{
			const char* buffer = TextFormat("[%s] ", key.first);
			this->Controls.Left.width = std::max(this->Controls.Left.width, (float)MeasureText(buffer, this->fontSize));
			this->Controls.Right.width = std::max(this->Controls.Right.width, (float)MeasureText(key.second, this->fontSize));
		}
	}
	this->Controls.Frame.width = this->Controls.Left.width + this->Controls.Right.width;
	this->Controls.Left.height = std::max((float)Display::HUD::hotkeyList.size(), (float)Display::HUD::hotkeyListAlternative.size()) * this->fontHeight;
	this->Controls.Right.height = this->Controls.Left.height;
	this->Controls.Frame.height = this->Controls.Left.height + this->fontHeight;

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
	for (const Rectangle& rect : { this->Data.Frame, this->Solver.Frame, this->Heuristics.Frame, this->Controls.Frame, this->Movement })
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
	this->Data.Frame.x = this->Frame.x + this->margin;
	this->Data.Frame.y = this->Frame.y + this->margin;
	Display::logRectangle("HUD.Data.Frame", this->Data.Frame);

	this->Data.Left.x = this->Data.Frame.x;
	this->Data.Left.y = this->Data.Frame.y + this->fontHeight;
	Display::logRectangle("HUD.Data.Left", this->Data.Left);

	this->Data.Right.x = this->Data.Left.x + this->Data.Left.width + (float)this->margin;
	this->Data.Right.y = this->Data.Left.y;
	Display::logRectangle("HUD.Data.Right", this->Data.Right);

TRACE_POSITION();
}

void	Display::HUD::configureSolverPosition(void)
{
TRACE_POSITION();
	this->Solver.Frame.x = this->Frame.x + this->margin;
	this->Solver.Frame.y = this->Data.Frame.y + this->Data.Frame.height + this->margin;
	Display::logRectangle("HUD.Solver.Frame", this->Solver.Frame);

	this->Solver.Left.x = this->Solver.Frame.x;
	this->Solver.Left.y = this->Solver.Frame.y + this->fontHeight;
	Display::logRectangle("HUD.Solver.Left", this->Solver.Left);

	this->Solver.Right.x = this->Solver.Left.x + this->Solver.Left.width + this->margin;
	this->Solver.Right.y = this->Solver.Left.y;
	Display::logRectangle("HUD.Solver.Right", this->Solver.Right);

TRACE_POSITION();
}

void	Display::HUD::configureHeuristicsPosition(void)
{
TRACE_POSITION();
	this->Heuristics.Frame.x = this->Frame.x + this->margin;
	this->Heuristics.Frame.y = this->Solver.Frame.y + this->Solver.Frame.height + this->margin;
	Display::logRectangle("HUD.Heuristics.Frame", this->Heuristics.Frame);
	this->Heuristics.Left.x = this->Heuristics.Frame.x;
	this->Heuristics.Left.y = this->Heuristics.Frame.y + this->fontHeight;
	Display::logRectangle("HUD.Heuristics.Left", this->Heuristics.Left);
	this->Heuristics.Right.x = this->Heuristics.Left.x + this->Heuristics.Left.width;
	this->Heuristics.Right.y = this->Heuristics.Left.y;
	Display::logRectangle("HUD.Heuristics.Right", this->Heuristics.Right);

TRACE_POSITION();
}

void	Display::HUD::configureControlsPosition(void)
{
TRACE_POSITION();
	this->Controls.Frame.x = this->Frame.x + this->margin;
	this->Controls.Frame.y = this->Heuristics.Frame.y + this->Heuristics.Frame.height + this->margin;
	Display::logRectangle("HUD.Controls.Frame", this->Controls.Frame);

	this->Controls.Left.x = this->Controls.Frame.x;
	this->Controls.Left.y = this->Controls.Frame.y + this->fontHeight;
	Display::logRectangle("HUD.Controls.Left", this->Controls.Left);

	this->Controls.Right.x = this->Controls.Left.x + this->Controls.Left.width;
	this->Controls.Right.y = this->Controls.Left.y;
	Display::logRectangle("HUD.Controls.Right", this->Controls.Right);

TRACE_POSITION();
}

void	Display::HUD::configureMovementPosition(void)
{
TRACE_POSITION();
	this->Movement.x = this->Frame.x + (this->Frame.width - this->Movement.width) / 2;
	this->Movement.y = this->Controls.Frame.y + this->Controls.Frame.height + this->margin;
	Display::logRectangle("HUD.Movement", this->Movement);

TRACE_POSITION();
}

void	Display::HUD::render(nPuzzle* puzzle, nPuzzle::State* state, bool alternative) const
{
TRACE_POSITION();
	this->renderFrame();
	this->renderData(puzzle, state);
	this->renderSolver(puzzle, alternative);
	this->renderHeuristics(state, puzzle->getHeuristicIndex(), alternative);
	this->renderControls(alternative);
	if (!alternative)
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
	DrawRectangleLinesEx(this->Data.Frame, 1, Color{255,23,23,255});
#endif
	const char*		buffer1;
	const char*		buffer2;
	static int32_t	oldPercentage = 0;

	DrawText("nPuzzle", this->Data.Frame.x, this->Data.Frame.y, this->fontSize, RED);
	for (size_t i = 0; ; i++)
	{
		switch (i)
		{
			case 0:
				buffer1 = TextFormat("Size:");
				if (puzzle)
					buffer2 = TextFormat("%ix%i", puzzle->getWidth(), puzzle->getHeight());
				else
					buffer2 = TextFormat("%ix%i", 0, 0);
				break;
			case 1:
				buffer1 = TextFormat("Solvability:");
				switch (puzzle->getSolvability())
				{
					case nPuzzle::Solvability::UNKNOWN:
						buffer2 = TextFormat("Unknown");
						break;
					case nPuzzle::Solvability::SOLVABLE:
						buffer2 = TextFormat("Solvable");
						break;
					case nPuzzle::Solvability::UNSOLVABLE:
						buffer2 = TextFormat("Unsolvable");
						break;
				}
				break;
			case 2:
				buffer1 = TextFormat("Moves:");
				if (state)
					buffer2 = TextFormat("%i", state->getCost());
				else
					buffer2 = TextFormat("N/A");
				break;
			default:
				goto endLoop;
		}
		DrawText(buffer1, this->Data.Left.x, this->Data.Left.y + i * this->fontHeight, this->fontSize, WHITE);
		DrawText(buffer2, this->Data.Right.x, this->Data.Right.y + i * this->fontHeight, this->fontSize, WHITE);
	}
	endLoop:
	return;

TRACE_POSITION();
}

void	Display::HUD::renderSolver(nPuzzle* puzzle, bool alternative) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Solver.Frame, 1, Color{255,23,23,255});
#endif
	const char*	buffer;
	int32_t	posY;

	// Header
	{
		posY = this->Solver.Frame.y;
		buffer = TextFormat("Solver");
		DrawText(buffer, this->Solver.Frame.x, posY, this->fontSize, RED);
	}
	// Mode
	{
		posY = this->Solver.Left.y;
		DrawText("Mode:", this->Solver.Left.x, posY, this->fontSize, WHITE);
		switch (puzzle->getSearchMode())
		{
			case nPuzzle::searchMode::GREEDY:
				buffer = TextFormat("%12s", "Greedy");
				break;
			case nPuzzle::searchMode::ASTAR:
				buffer = TextFormat("%12s", "A*");
				break;
			case nPuzzle::searchMode::UNIFORM:
				buffer = TextFormat("%12s", "Uniform-cost");
				break;
			default:
				buffer = TextFormat("N/A");
		}
		DrawText(buffer, this->Solver.Right.x, posY, this->fontSize, WHITE);
	}
	// Queue
	{
		posY = this->Solver.Left.y + this->fontHeight;
		DrawText("Queue:", this->Solver.Left.x, posY, this->fontSize, WHITE);
		buffer = TextFormat("%12i", puzzle->getQueueSize());
		DrawText(buffer, this->Solver.Right.x, posY, this->fontSize, WHITE);
	}
	// Progress
	{
		posY = this->Solver.Frame.y + this->Solver.Frame.height - this->fontHeight * 2;
		static int32_t	oldPercentage = 0;
		int32_t	h = puzzle->getBestSolverHeuristic();
		int32_t g = puzzle->getQueueState().getCost();
		int32_t	percentage = (g + h == 0) ? 0 : (g * 100) / (g + h);
		if (percentage < oldPercentage)
			--oldPercentage;
		else
			oldPercentage = percentage;
		DrawRectangle(this->Solver.Frame.x, posY, this->Solver.Frame.width * oldPercentage / 100, this->fontHeight, GRAY);
		DrawRectangle(this->Solver.Frame.x, posY, this->Solver.Frame.width * percentage / 100, this->fontHeight, WHITE);
		DrawRectangleLines(this->Solver.Frame.x, posY, this->Solver.Frame.width, this->fontHeight, WHITE);

		int32_t	adjustX = MeasureText("G: 000",this->fontSize) / 2;
		buffer = TextFormat("G: %3i", g);
		DrawText(buffer, this->Solver.Frame.x + this->Solver.Frame.width / 3 - adjustX, posY, this->fontSize, ORANGE);
		switch (h)
		{
			case -2:	buffer = TextFormat("H: %3s", "??");	break;
			default:
				if (h < 0)
					buffer = TextFormat("H: %3s", "err");
				else
					buffer = TextFormat("H: %3i", h);
				break;
		}
		DrawText(buffer, this->Solver.Frame.x + this->Solver.Frame.width * 2 / 3 - adjustX, posY, this->fontSize, ORANGE);
	}
	// Movement
	if (alternative)
	{
		int	posY = this->Solver.Frame.y + this->Solver.Frame.height - this->fontHeight;
		this->DrawArrow(this->Solver.Frame.x, posY, this->fontHeight, 2);
		this->DrawArrow(this->Solver.Frame.x + this->fontHeight, posY, this->fontHeight, 3);
		DrawText(" Change Mode", this->Solver.Frame.x + this->fontHeight * 2, posY, this->fontSize, WHITE);
	}
}

void	Display::HUD::renderHeuristics(nPuzzle::State* state, int32_t h, bool alternative) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Heuristics.Frame, 1, Color{255,23,23,255});
#endif
	const char* buffer;
	Color	selected{255, 127, 0, 255};
	Color	unselected = WHITE;

	DrawText("Heuristics", this->Heuristics.Frame.x, this->Heuristics.Frame.y, this->fontSize, RED);
	for (int32_t line = 0; line < heuristic::size; ++line)
	{
		int posY = this->Heuristics.Left.y + line * this->fontHeight;
		DrawText(heuristic::function[line].name, this->Heuristics.Left.x, posY, this->fontSize, (line == h) ? selected : unselected);
		int32_t	h = state->getHeuristic(line);
		switch (h)
		{
			case	-2:	buffer = TextFormat(" %4s", "??");	break;
			default:
				if (h < 0)
					buffer = TextFormat(" %4s", "err");
				else
					buffer = TextFormat(" %4i", h);	break;
		}
		DrawText(buffer, this->Heuristics.Right.x, posY, this->fontSize, (line == h) ? selected : unselected);
	}
	if (alternative)
	{
		int posY = this->Heuristics.Frame.y + this->Heuristics.Frame.height - this->fontHeight;
		DrawArrow(this->Heuristics.Frame.x, posY, this->fontHeight, 0);
		DrawArrow(this->Heuristics.Frame.x + this->fontHeight, posY, this->fontHeight, 1);
		DrawText(" Change heuristic", this->Heuristics.Frame.x + this->fontHeight * 2, posY, this->fontSize, WHITE);
	}
TRACE_POSITION();
}

void	Display::HUD::renderControls(bool alternative) const
{
TRACE_POSITION();
#if DEBUG >= DEBUG_DEBUG
	DrawRectangleLinesEx(this->Controls.Frame, 1, Color{23,255,23,255});
#endif
	DrawText("Controls", this->Controls.Frame.x, this->Controls.Frame.y, this->fontSize, RED);

	const char*	buffer;
	size_t	i = 0;
	const std::vector<std::pair<const char*, const char*> >&	list = (alternative) ? Display::HUD::hotkeyListAlternative : Display::HUD::hotkeyList;

	for (auto it = list.begin(); it != list.end(); ++it, ++i)
{
		buffer = TextFormat("[%s]", it->first);
		DrawText(buffer, this->Controls.Left.x, this->Controls.Left.y + i * this->fontHeight, this->fontSize, WHITE);
		DrawText(it->second, this->Controls.Right.x, this->Controls.Right.y + i * this->fontHeight, this->fontSize, WHITE);
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
	//arrow UP
	int32_t	posX = this->Movement.x + this->Movement.width / 3;
	int32_t	posY = this->Movement.y;
	this->DrawArrow(posX, posY, this->Movement.width / 3, 0);
	//Arrow DOWN
	posY += this->Movement.height * 2 / 3;
	this->DrawArrow(posX, posY, this->Movement.width / 3, 1);
	// Arrow LEFT
	posX = this->Movement.x;
	posY = this->Movement.y + this->Movement.height / 3;
	this->DrawArrow(posX, posY, this->Movement.width / 3, 2);
	// Arrow RIGHT
	posX += this->Movement.width * 2 / 3;
	this->DrawArrow(posX, posY, this->Movement.width / 3, 3);
TRACE_POSITION();
}

void	Display::HUD::DrawArrow(int32_t x, int32_t y, int32_t size, int32_t dir) const
{
	const float cx = x + size * 0.5f;
	const float cy = y + size * 0.5f;
	const float margin = size * 0.2f;
	const float head = size * 0.25f;

	// Draw line
	if (dir == 0 || dir == 1)
		DrawLineEx({cx, y + margin}, {cx, y + size - margin}, 2.0f, WHITE);
	else
		DrawLineEx({x + margin, cy}, {x + size - margin, cy}, 2.0f, WHITE);
	// Draw head
	switch (dir)
	{
		// UP
		case 0:
		DrawLineEx({cx, y + margin}, {cx - head, y + margin + head}, 2.0f, WHITE);
		DrawLineEx({cx, y + margin}, {cx + head, y + margin + head}, 2.0f, WHITE);
			break;
		// DOWN
		case 1:
			DrawLineEx({cx, y + size - margin}, {cx - head, y + size - margin - head}, 2.0f, WHITE);
			DrawLineEx({cx, y + size - margin}, {cx + head, y + size - margin - head}, 2.0f, WHITE);
			break;
		// LEFT
		case 2:
			DrawLineEx({x + margin, cy}, {x + margin + head, cy - head}, 2.0f, WHITE);
			DrawLineEx({x + margin, cy}, {x + margin + head, cy + head}, 2.0f, WHITE);
			break;
		// RIGHT
		case 3:
			DrawLineEx({x + size - margin, cy}, {x + size - margin - head, cy - head}, 2.0f, WHITE);
			DrawLineEx({x + size - margin, cy}, {x + size - margin - head, cy + head}, 2.0f, WHITE);
			break;
		default:
			break;
	}

}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
