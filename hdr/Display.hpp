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
# pragma region "Nested Objects"
	private:
		struct	HUD;
# pragma endregion "Nested Objects"

	private:
		nPuzzle*	puzzle;
		HUD*		HUD;

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
		void	renderBoard(const nPuzzle::Board& board);
		void	renderTiles(const nPuzzle::Board& board);

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
		void	render(void);
		void	renderAsStartState(void);
		void	renderAsCurrentState(void);
		void	renderAsQueueState(void);
		void	renderAsTargetState(void);

		// Display	&operator=(const Display &src);
};

#endif
