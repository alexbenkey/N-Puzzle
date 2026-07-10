/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:44:29 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/09 18:44:57 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "colors.hpp"

#include <iostream>	// std::

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

Display::HUD::HUD()
{
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;

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
	std::cout	<< C_DRED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
}

/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	Display::HUD::setMargin(const int& margin, bool updateSizes)
{
	this->margin = margin;
	if (updateSizes)
		this->configureSizes();
}

void	Display::HUD::setFontsize(const float& fontSize, bool updateSizes)
{
	this->fontSize = fontSize;
	this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y;
	if (!this->fontHeight)
		this->fontHeight = this->fontSize;
	if (updateSizes)
		this->configureSizes();
}

void	Display::HUD::configureSizes(bool updatePositions)
{
	LOG_AS_TRACE();
	this->configureDataSize(false);
	this->configureControlSize(false);
	this->configureMovementSize(false);
	this->configureFrameSize(updatePositions);
}

void	Display::HUD::configureDataSize(bool updateFrame)
{
	LOG_AS_TRACE();
	this->Data.width = MeasureText("  [M]anhattan: 00", this->fontSize);
	this->Data.height = 7 * this->fontHeight;
	Display::logRectangle("HUD.Data", this->Data);
	if (updateFrame)
		this->configureFrameSize();
}

void	Display::HUD::configureControlSize(bool updateFrame)
{
	LOG_AS_TRACE();
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
}

void	Display::HUD::configureMovementSize(bool updateFrame)
{
	LOG_AS_TRACE();
	this->Movement.width = this->margin * 5;
	this->Movement.height = this->Movement.width;
	Display::logRectangle("HUD.Movement", this->Movement);
	if (updateFrame)
		this->configureFrameSize();
}

void	Display::HUD::configureFrameSize(bool updatePositions)
{
	LOG_AS_TRACE();
	this->Frame.width = 0;
	this->Frame.height = (float)this->margin;
	for (const Rectangle& rect : { this->Data, this->Controls, this->Movement })
	{
		this->Frame.width = std::max(this->Frame.width, rect.width);
		this->Frame.height += rect.height + this->margin;
	}
	this->Frame.width += 2 * (float)this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);
	if (updatePositions)
		this->configurePositions();
}

void	Display::HUD::configurePositions(void)
{
	LOG_AS_TRACE();
	this->configureFramePosition();
	this->configureDataPosition();
	this->configureControlsPosition();
	this->configureMovementPosition();
}

void	Display::HUD::configureFramePosition(void)
{
	LOG_AS_TRACE();
	this->Frame.x = this->margin;
	this->Frame.y = this->margin;
	Display::logRectangle("HUD.Frame", this->Frame);
}

void	Display::HUD::configureDataPosition(void)
{
	LOG_AS_TRACE();
	this->Data.x = this->Frame.x + this->margin;
	this->Data.y = this->Frame.y + this->margin;
	Display::logRectangle("HUD.Data", this->Data);
}

void	Display::HUD::configureControlsPosition(void)
{
	LOG_AS_TRACE();
	this->Controls.x = this->Frame.x + this->margin;
	this->Controls.y = this->Data.y + this->Data.height + this->margin;
	Display::logRectangle("HUD.Controls", this->Controls);
}

void	Display::HUD::configureMovementPosition(void)
{
	LOG_AS_TRACE();
	this->Movement.x = this->Frame.x + (this->Frame.width - this->Movement.width) / 2;
	this->Movement.y = this->Controls.y + this->Controls.height + this->margin;
	Display::logRectangle("HUD.Movement", this->Movement);
}

void	Display::HUD::render(void) const
{
	this->renderFrame();
	this->renderData(nullptr);
	this->renderControls();
	this->renderMovement();
}

void	Display::HUD::renderFrame(void) const
{
	DrawRectangleRec(this->Frame, Color{23,23,23,255});
}

void	Display::HUD::renderData(nPuzzle* puzzle) const
{
	const char*	buffer;

	// DrawRectangleLinesEx(this->Data, 1, Color{255,23,23,255});
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
			case 3:
				buffer = TextFormat("Heuristics");
				break;
			case 4:
				if (puzzle)
					buffer = TextFormat("  [M]anhattan: %i", 0);
				else
					buffer = TextFormat("  [M]anhattan: %s", "N/A");
				break;
			default:
				goto endLoop;
		}
		DrawText(buffer, this->Data.x, this->Data.y + i * this->fontHeight, this->fontSize, WHITE);
	}
	endLoop:
	return;
}

void	Display::HUD::renderControls(void) const
{
	const char*	buffer;
	size_t		i;

	// DrawRectangleLinesEx(this->Controls, 1, Color{23,255,23,255});
	i = 0;
	for (auto it = Display::hotkeyList.begin(); it != Display::hotkeyList.end(); ++it, ++i)
	{
		buffer = TextFormat("[%c] %s", it->first, it->second.c_str());
		DrawText(buffer, this->Controls.x, this->Controls.y + i * this->fontHeight, this->fontSize, WHITE);
	}
}

void	Display::HUD::renderMovement(void) const
{
	int	length;
	int width;

	// DrawRectangleLinesEx(this->Movement, 1, Color{23,23,255,255});
	length = std::min(this->Movement.width, this->Movement.height);
	width = length / 3;
	DrawRectangle(this->Movement.x, this->Movement.y + (length - width) / 2, length, width, Color{192,192,192,255});
	DrawRectangle(this->Movement.x + (length - width) / 2, this->Movement.y, width, length, Color{192,192,192,255});
}

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */
