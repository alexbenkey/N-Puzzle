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

# include "Errors.hpp"

class nPuzzleState
{
	private:
		class Tile
		{
			private:
				int32_t	value;
				int32_t xPos;
				int32_t yPos;
				
			public:
				Tile(void);
				Tile(const Tile &src);
				~Tile(void);

				int32_t	getVal(void) const	{ return (this->value); } 
				void	setVal(int32_t value) { this->value = value; }
				int32_t	getxPos(void) const { return (this->xPos); }
				void	setxPos(int32_t xPos) { this->xPos = xPos; } 
				int32_t getyPos(void) const {return (this->yPos); }
				void	setyPos(int32_t yPos) { this->yPos = yPos; }  

				Tile	&operator=(const Tile &src);
		};

		std::vector<std::vector<Tile> >	tiles;

		bool	validPuzzleContent(void) const;
		bool	validPuzzlePlacement(void) const;
		Tile*   Emptysquare;

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
		Tile&   getTile(const int32_t value);
		Tile&	getTile(const int32_t x, const int32_t y) { return this->tiles[y][x]; }
		
		const Tile&	getTile(const int32_t x, const int32_t y) const { return this->tiles[y][x]; }
		// Tile&	getTile(int32_t x, int32_t y){ return tiles[y][x]; }
		int		getTileValue(const int32_t x, const int32_t y) const	{ return this->getTile(x, y).getVal(); }
		void	printPuzzle(void) const;
		bool	validPuzzle(void) const;
		void	printTilePos(const Tile& Tile) const;

		void 	setEmptysquare(Tile* tile) { this->Emptysquare = tile; }
		Tile* 	getEmptysquare(void) const { return this->Emptysquare; }

		void 	moveTile(Tile& tile);
		void 	moveUp(void);
		void 	moveDown(void);
		void 	moveLeft(void);
		void 	moveRight(void);

		nPuzzleState	&operator=(const nPuzzleState &src);
};

#endif