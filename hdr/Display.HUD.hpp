/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.HUD.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:26:59 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:29:31 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HUD_HPP
# define DISPLAY_HUD_HPP

# include "Display.hpp"

struct Display::HUD
{
	private:
		int margin;
		float	fontSize;
		float	fontHeight;

		Rectangle	Frame;
		Rectangle	Data;
		Rectangle	Heuristics;
		Rectangle	Controls;
		Rectangle	Movement;
		// Positions
		void	configureFramePosition(void);
		void	configureDataPosition(void);
		void	configureHeuristicsPosition(void);
		void	configureControlsPosition(void);
		void	configureMovementPosition(void);
		// Render
		void	renderFrame(void) const;
		void	renderData(nPuzzle* puzzle, nPuzzle::State* state) const;
		void	renderHeuristics(nPuzzle::State* state) const;
		void	renderControls(void) const;
		void	renderMovement(void) const;
	
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
		void	configureHeuristicsSize(bool updateFrame = true);
		void	configureControlSize(bool updateFrame = true);
		void	configureMovementSize(bool updateFrame = true);
		void	configureFrameSize(bool updatePositions = true);
		// Positions
		void	configurePositions(void);
		// Render
		void	render(nPuzzle* puzzle, nPuzzle::State* state) const;
};

#endif
