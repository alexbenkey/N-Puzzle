/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Display.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/02 17:58:28 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/07/02 17:58:28 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include "../assets/raylib/src/raylib.h"
#include "nPuzzle.hpp"

#include <unordered_map>
#include <string>

// struct hotKey
// {
// 	std::string_view	key;
// 	std::string_view	description;
// };

#define DEFAULT_MARGIN		23
#define DEFAULT_FONTSIZE	20

class Display
{
	private:
		nPuzzle*	puzzle;

		class HUD
		{
			public:
				int margin;

				Rectangle	Frame;
				Rectangle	Data;
				Rectangle	Controls;
				Rectangle	Movement;

			public:
				HUD()
				{
					this->margin = 23;
					this->Frame.width = this->margin;
					this->Frame.height = this->margin;
					this->Data.width = 1;
					this->Data.height = 1;
					this->Controls.width = 1;
					this->Controls.height = 1;
					this->Movement.width = 1;
					this->Movement.height = 1;
				}
				void	adjustSizes()
				{
					this->Frame.width = std::max(this->Data.width, this->Controls.width) + 2 * margin;
					// this->width = (int)this->Frame.width;

					this->Frame.height = this->Data.height + this->Controls.height + 2 * margin;
					// this->height = (int)this->Frame.height;
				}
		};
		struct HUD	HUD;
		Rectangle	Frame;
		Rectangle	tile;

		float	fontSize;
		float	fontHeight;
		int		margin;

		static std::unordered_map<char, std::string>	hotkeyList;

		// Sizes
		void	configureMinimumSizes(void);
		void	configureMaximumSizes(void);

		void	configureHUDDataSize(void);
		void	configureHUDControlSize(void);
		void	configureHUDMovementSize(void);
		void	configureHUDFrameSize(void);
		void	configureMinimumFrameSizes(void);
		void	configureFrameSize(void);
		void	configureTileSize(void);

		// Positions
		void	configurePositions(void);
		void	configureHUDFramePosition(void);
		void	configureHUDDataPosition(void);
		void	configureHUDControlsPosition(void);
		void	configureHUDMovementPosition(void);
		void	configureFramePosition(void);

		// Log
		static void	logRectangle(const char* name, const Rectangle& rect);

		// Rendering
		void	renderHUDData();
		void	renderHUDControls();
		void	renderHUDMovement();
		void	renderTiles(nPuzzleState& state);

	protected:

	public:
		Display(nPuzzle* puzzle);
		Display(const Display &src);
		~Display(void);

		// Sizes
		void	configureSizes(void);
		void	reconfigure(void);
		bool	setFontSize(const float size);
		bool	setMargin(const int margin);
		// Rendering
		void	renderScreen(void);
		void	renderCurrentState()	{ this->renderTiles(this->puzzle->getCurrentState()); }
		void	renderTargetState()		{ this->renderTiles(this->puzzle->getTargetState()); }
		void	renderStartState()		{ this->renderTiles(this->puzzle->getStartState()); }

		Display	&operator=(const Display &src);
};

#endif
