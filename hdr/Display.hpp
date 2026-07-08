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
		Rectangle	HUD;
		Rectangle	HUDData;
		Rectangle	HUDControls;
		Rectangle	Frame;
		Rectangle	tile;

		float	fontSize;
		float	fontHeight;
		int		margin;

		static std::unordered_map<char, std::string>	hotkeyList;

		void	getMinHUDWidth();
		int	getMinHUDKeyWidth();
		int	getMinHUDDescriptionWidth();

	protected:

	public:
		Display(nPuzzle* puzzle);
		Display(const Display &src);
		~Display(void);

		void	setFontSize(const float size)	{ this->fontSize = size; this->fontHeight = MeasureTextEx(GetFontDefault(), "X", this->fontSize, 0).y; }
		void	setMargin(const int margin)	{ this->margin = margin; }

		void	adjustScale();

		void	renderHUD();
		void	renderTiles(nPuzzleState& state);
		void	renderCurrentState()	{ this->renderTiles(this->puzzle->getCurrentState()); }
		void	renderTargetState()		{ this->renderTiles(this->puzzle->getTargetState()); }
		void	renderStartState()		{ this->renderTiles(this->puzzle->getStartState()); }

		Display	&operator=(const Display &src);
};

#endif
