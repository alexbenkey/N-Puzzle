/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:32:56 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/10 16:33:01 by ohengelm         ###   ########.fr       */
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
	private:
		Board	board;
		struct Position {
			int32_t x;
			int32_t y;
		}; 

		const int32_t&	width;
		const int32_t&	height;
		const int32_t&	size;
		const int32_t&	heuristicIndex;
		std::map<int32_t, int32_t>	heuristic;
		int32_t	cost = 0;
		int32_t	score = 0;
		nPuzzle::State *previous = nullptr;
		nPuzzle::searchMode searchMode = nPuzzle::searchMode::ASTAR;

		Position emptyPos = {0, 0};

		bool	validPuzzleContent(void) const;
		bool	validPuzzlePlacement(void) const;

	public:
		State(const int32_t& width, const int32_t& height, const int32_t& size, const int32_t& heuristicIndex);
		State(const State &src);
		~State(void);

		int32_t	getPuzzleHeight(void) const { return this->height; }
		int32_t	getPuzzleWidth(void) const { return this->width; } 
		int32_t	getPuzzleSize(void) const { return this->size; }
		// int32_t	getUsedHeuristic(void) const {return this->usedHeuristic; }

		// bool	setUsedHeuristic(int32_t value);

		void	setSearchMode(nPuzzle::searchMode mode) {this->searchMode = mode;}

		void	addTile(const int32_t value, const int32_t x, const int32_t y) { this->board.addTile(value, x, y); }
		const nPuzzle::Board&	getBoard() const { return this->board; }
		const nPuzzle::Board::Tile&	getTile(const int32_t value) const;
		const nPuzzle::Board::Tile&	getTile(const int32_t x, const int32_t y) const;
		const nPuzzle::Board::Tile&	getEmptyTile() const { return this->board.getEmptyTile(); }

		void setPrevious(nPuzzle::State *state) {this->previous = state;}
		const nPuzzle::State *getPrevious(void) const { return this->previous;}

		// void	printPuzzle(void) const;
		bool	validPuzzle(void) const;
		// void	printTilePos(const Tile& Tile) const;
		int32_t	getTileValue(const int32_t x, const int32_t y) const;

		void	setEmptyPos(int32_t x, int32_t y) { emptyPos = {x, y}; }
		Position	getEmptyPos() const {return emptyPos; }

		void	moveTile(const nPuzzle::Board::Tile& tile);
		void	increaseCost(void) { ++this->cost; };

		bool	move(Direction direction);

		void	calculateAllHeuristics(const nPuzzle::Board& target);
		void	calculateOneHeuristic(const nPuzzle::Board& target);
		void	calculateOneHeuristic(const nPuzzle::Board& target, int32_t h);
		int32_t	getHeuristic(int32_t h) const;

		int32_t	getCost(void) const	{ return (this->cost); }
		// int32_t	getHeuristic(void) const {return (this->heuristic); }

		bool	sameBoard(const State &rhs) const noexcept;

		State	&operator=(const State &src);

		bool	operator<(const State &rhs) const noexcept;
		bool	operator<=(const State &rhs) const noexcept;
		bool	operator>(const State &rhs) const noexcept;
		bool	operator>=(const State &rhs) const noexcept;

		friend std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state);
};

#endif
