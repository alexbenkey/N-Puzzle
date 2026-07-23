/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:32:56 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:38:27 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_STATE_HPP
# define NPUZZLE_STATE_HPP

# include "nPuzzle.hpp"
# include "nPuzzle.Board.hpp"

# include <aio.h>	// int32_t
# include <vector>	// std::vector
# include <map>	// std::map

class nPuzzle::State
{
// # pragma region "Nested Classes"
// 	public:
// 		class		Tile;
// # pragma endregion "Nested Classes"
	private:

	protected: 
		// std::vector<std::vector<Tile> >	tiles;
		Board	board;

		struct Position {
			int32_t x;
			int32_t y;
		}; 

		int32_t	width;
		int32_t	height;
		int32_t	size;
		std::map<int32_t, int32_t>	heuristic;
		int32_t   usedHeuristic = 1;
		int32_t	cost = 0;

		Position emptyPos = {0, 0};

		bool	validPuzzleContent(void) const;
		bool	validPuzzlePlacement(void) const;

	public:
		State(void);
		State(const int32_t size);
		State(const int32_t width, const int32_t height);
		State(const State &src);
		~State(void);

		int32_t getPuzzleHeight(void) const {return this->height; }
		int32_t getPuzzleWidth(void) const {return this->width; } 
		int32_t getPuzzleSize(void) const {return this->size; }
		int32_t getUsedHeuristic(void) const {return this->usedHeuristic; }

		bool	setUsedHeuristic(int32_t value);
		void	generateTiles(void);

		void	addTile(const int32_t value, const int32_t x, const int32_t y) { this->board.addTile(value, x, y); }
		// Tile&		getTile(const int32_t value);
		const nPuzzle::Board::Tile&	getTile(const int32_t value) const;
# warning maybe this should be removed in favor of a swapTiles function
		// nPuzzle::Board::Tile&		getTile(const int32_t x, const int32_t y);
		const nPuzzle::Board::Tile&	getTile(const int32_t x, const int32_t y) const;
		// Tile& 		getEmptyTile() { return tiles[emptyPos.y][emptyPos.x]; }
		const nPuzzle::Board::Tile&	getEmptyTile() const { return this->board.getEmptyTile(); }
		const nPuzzle::Board&	getBoard() const { return this->board; }


		// void	printPuzzle(void) const;
		bool	validPuzzle(void) const;
		// void	printTilePos(const Tile& Tile) const;
		int32_t	getTileValue(const int32_t x, const int32_t y) const;

		void setEmptyPos(int32_t x, int32_t y) { emptyPos = {x, y}; }
		Position getEmptyPos() const {return emptyPos; }

		void 	moveTile(const nPuzzle::Board::Tile& tile);
		void 	increaseCost(void) { ++this->cost; };

		bool	move(Direction direction);
	
		void	calculateHeuristic(const nPuzzle::Board& target);
		void	calculateHeuristic(int32_t h, const nPuzzle::Board& target);
		int32_t	getHeuristic(int32_t h) const;

		int32_t	getCost(void) const	{ return (this->cost); }
		// int32_t getHeuristic(void) const {return (this->heuristic); }

		bool			sameState(const State &rhs) const noexcept;
		
		State	&operator=(const State &src);

		bool			operator<(const State &rhs) const noexcept;
		bool			operator<=(const State &rhs) const noexcept;
		bool			operator>(const State &rhs) const noexcept;
		bool			operator>=(const State &rhs) const noexcept;

		friend std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state);
};

#endif