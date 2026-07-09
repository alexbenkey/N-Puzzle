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
	public:
		class Tile
		{
			private:
				int32_t	value;
				int32_t xPos;
				int32_t yPos;
				
			public:
				Tile(void);
        		Tile(const Tile& src);

				~Tile(void);

				int32_t	getVal(void) const	{ return value; } 
				void	setVal(int32_t v) { value = v;}
				int32_t	getxPos(void) const { return xPos; }
				void	setxPos(int32_t x) { xPos = x; } 
				int32_t getyPos(void) const {return yPos; }
				void	setyPos(int32_t y) { yPos = y; }  

				Tile& operator=(const Tile& src);
		};

	private:
		std::vector<std::vector<Tile> >	tiles;

		struct Position {
			int32_t x;
			int32_t y;
		}; 

		const int32_t	width;
		const int32_t	height;
		const int32_t	size;

		Position emptyPos = {0, 0};

		bool	validPuzzleContent(void) const;
		bool	validPuzzlePlacement(void) const;

	public:
		nPuzzleState(const int32_t size);
		nPuzzleState(const int32_t width, const int32_t height);
		nPuzzleState(const nPuzzleState &src);
		~nPuzzleState(void);

		int32_t getPuzzleHeight(void) const {return this->height; }
		int32_t getPuzzleWidth(void) const {return this->width; } 
		int32_t getPuzzleSize(void) const {return this->size; }

		void	generateTiles(void);
		Tile&   getTile(const int32_t value);
		Tile&	getTile(const int32_t x, const int32_t y) { return tiles[y][x]; }
		
		const Tile&	getTile(const int32_t x, const int32_t y) const { return tiles[y][x]; }
		// Tile&	getTile(int32_t x, int32_t y){ return tiles[y][x]; }

		void	printPuzzle(void) const;
		bool	validPuzzle(void) const;
		void	printTilePos(const Tile& Tile) const;

    	Tile& getEmptyTile() { return tiles[emptyPos.y][emptyPos.x]; }
    	const Tile& getEmptyTile() const { return tiles[emptyPos.y][emptyPos.x]; }

		void setEmptyPos(int32_t x, int32_t y) { emptyPos = {x, y}; }
		Position getEmptyPos() const {return emptyPos; }

		void 	moveTile(Tile& tile);

		void 	moveUp(void);
		void 	moveDown(void);
		void 	moveLeft(void);
		void 	moveRight(void);

		nPuzzleState	&operator=(const nPuzzleState &src);
};

#endif