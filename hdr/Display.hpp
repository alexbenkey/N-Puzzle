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

class Display
{
	private:
		nPuzzle*	puzzle;
		// int			rows;
		// int			cols;
		Rectangle	Frame;
		Rectangle	tile;

	protected:

	public:
		Display(nPuzzle* puzzle);
		Display(const Display &src);
		~Display(void);

		void	adjustScale();
		// void	render();
		void	renderHUD();
		void	renderTiles(nPuzzleState& state);
		void	renderCurrentState()	{ this->renderTiles(this->puzzle->getCurrentState()); }
		void	renderTargetState()		{ this->renderTiles(this->puzzle->getTargetState()); }
		void	renderStartState()		{ this->renderTiles(this->puzzle->getStartState()); }

		Display	&operator=(const Display &src);
};

#endif
