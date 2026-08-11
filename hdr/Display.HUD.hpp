/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:26:59 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/11 18:59:22 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HUD_HPP
# define DISPLAY_HUD_HPP

# include "Display.hpp"

struct Display::HUD
{
	private:
		static std::vector<std::pair<const char*, const char*> >	hotkeyList;
		static std::vector<std::pair<const char*, const char*> >	hotkeyListAlternative;

		int margin;
		float	fontSize;
		float	fontHeight;

		struct DoubleRectangle
		{
			Rectangle	Frame;
			Rectangle	Left;
			Rectangle	Right;
		};
		Rectangle		Frame;
		DoubleRectangle	Data;
		DoubleRectangle	Solver;
		DoubleRectangle	Heuristics;
		DoubleRectangle	Controls;
		Rectangle		Movement;
		// Positions
		void	configureFramePosition(void);
		void	configureDataPosition(void);
		void	configureSolverPosition(void);
		void	configureHeuristicsPosition(void);
		void	configureControlsPosition(void);
		void	configureMovementPosition(void);
		// Render
		void	renderFrame(void) const;
		void	renderData(nPuzzle* puzzle, nPuzzle::State* state) const;
		void	renderSolver(nPuzzle* puzzle, bool alternative = false) const;
		void	renderHeuristics(nPuzzle::State* state, int32_t h, bool alternative = false) const;
		void	renderControls(bool alternative = false) const;
		void	renderMovement(void) const;

		void	DrawArrow(int32_t x, int32_t y, int32_t size, int32_t dir) const;

	public:
		HUD(void);
		~HUD(void);

		void	setMargin(const int& margin, bool updateSizes = true);
		void	setFontsize(const float& fontSize, bool updateSizes = true);

		float	width(void) const	{ return (this->Frame.width); }
		float	height(void) const	{ return (this->Frame.height); }
		float	x(void) const		{ return (this->Frame.x); }
		float	y(void) const		{ return (this->Frame.y); }
		// Sizes
		void	configureSizes(bool updatePositions = false);
		void	configureDataSize(bool updateFrame = true);
		void	configureSolverSize(bool updateFrame = true);
		void	configureHeuristicsSize(bool updateFrame = true);
		void	configureControlSize(bool updateFrame = true);
		void	configureMovementSize(bool updateFrame = true);
		void	configureFrameSize(bool updatePositions = true);
		// Positions
		void	configurePositions(void);
		// Render
		void	render(nPuzzle* puzzle, nPuzzle::State* state, bool alternative = false) const;
};

#endif
