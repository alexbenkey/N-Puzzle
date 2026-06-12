/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzleState.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLESTATE_HPP
# define NPUZZLESTATE_HPP

# include <aio.h>	// size_t int32_t

#include <vector>

class nPuzzleState
{
	private:
		class Tile
		{
			private:
				int32_t	value;
				
			public:
				Tile(void);
				Tile(const Tile &src);
				~Tile(void);

				int32_t	get(void) const	{ return (this->value); }
				void	set(int16_t value) { this->value = value; }

				Tile	&operator=(const Tile &src);
		};

		std::vector<std::vector<Tile> >	tiles;

		bool	validPuzzleContent(void) const;
		bool	validPuzzlePlacement(void) const;

	protected:
		const int32_t	width;
		const int32_t	height;
		const int32_t	size;

	public:
		nPuzzleState(const int32_t size);
		nPuzzleState(const int32_t width, const int32_t height);
		nPuzzleState(const nPuzzleState &src);
		~nPuzzleState(void);

		void	generateTiles(void);
		Tile&	getTile(const int32_t x, const int32_t y) { return this->tiles[y][x]; }
		const Tile&	getTile(const int32_t x, const int32_t y) const { return this->tiles[y][x]; }
		// Tile&	getTile(int32_t x, int32_t y){ return tiles[y][x]; }
		void	printPuzzle(void) const;
		bool	validPuzzle(void) const;

		nPuzzleState	&operator=(const nPuzzleState &src);
};

#endif
