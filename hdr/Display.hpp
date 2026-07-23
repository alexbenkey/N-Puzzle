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

# include "Errors.hpp"
# include <cstring>	// strrchr
# define LOG_LINE(level, format, ...) \
    TraceLog(level, \
        C_DGRAY "%s" C_RESET ":" C_DORANGE "%s" C_RESET "[" C_ORANGE "%i" C_RESET "] " format, \
        strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__, \
        __func__, \
        __LINE__, \
        ##__VA_ARGS__)

# define LOG_AS_TRACE(format, ...) LOG_LINE(LOG_TRACE, format, ##__VA_ARGS__)
# define LOG_AS_DEBUG(format, ...) LOG_LINE(LOG_DEBUG, format, ##__VA_ARGS__)
# define LOG_AS_INFO(format, ...)  LOG_LINE(LOG_INFO, format, ##__VA_ARGS__)
# define LOG_AS_WARN(format, ...)  LOG_LINE(LOG_WARNING, format, ##__VA_ARGS__)
# define LOG_AS_ERROR(format, ...) LOG_LINE(LOG_ERROR, format, ##__VA_ARGS__)

# include "raylib.h"
# include "nPuzzle.hpp"

# include <unordered_map>
# include <string>

# define DEFAULT_MARGIN		23
# define DEFAULT_FONTSIZE	20

class Display
{
	private:
		nPuzzle*	puzzle;

		struct HUD
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
				void	renderData(nPuzzle* puzzle, nPuzzleState* state) const;
				void	renderHeuristics(nPuzzleState* state) const;
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
				void	render(nPuzzle* puzzle, nPuzzleState* state) const;
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
		void	configureScreen(void);

		void	configureMinimumFrameSizes(void);
		void	configureFrameSize(void);
		void	configureTileSize(void);

		// Positions
		void	configurePositions(void);
		void	configureFramePosition(void);

		// Log
		static void	logRectangle(const char* name, const Rectangle& rect);

		// Rendering
		void	renderState(nPuzzleState* state);
		void	renderTiles(nPuzzleState& state);

	protected:

	public:
		Display(nPuzzle* puzzle);
		// Display(const Display &src);
		~Display(void);

		void	setPuzzle(nPuzzle* puzzle);

		// Sizes
		void	configureSizes(void);
		void	reconfigure(void);
		bool	setFontSize(const float size, bool updateSizes = true, bool includeHUD = true);
		bool	setMargin(const int margin, bool updateSizes = true, bool includeHUD = true);
		// Rendering
		void	render(void)				{ this->renderAsCurrentState(); }
		void	renderAsStartState(void)	{ if (this->puzzle) this->renderState(&this->puzzle->getStartState()); }
		void	renderAsCurrentState(void)	{ if (this->puzzle) this->renderState(&this->puzzle->getCurrentState()); }
		void	renderAsQueueState(void)	{ if (this->puzzle) this->renderState(&this->puzzle->getQueueState()); }
		void	renderAsTargetState(void)	{ if (this->puzzle) this->renderState(&this->puzzle->getTargetState()); }

		// Display	&operator=(const Display &src);
};

#endif
