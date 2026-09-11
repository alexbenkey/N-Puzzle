/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.State.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:32:56 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/02 18:24:46 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_STATE_HPP
# define NPUZZLE_STATE_HPP

# include "nPuzzle.hpp"
# include "nPuzzle.Board.hpp"

# include <aio.h>	// int32_t
# include <map>	// std::map

class nPuzzle::State
{
	private:
		Board	board;

		const int32_t&	width;
		const int32_t&	height;
		const int32_t&	size;
		const int32_t&	heuristicIndex;
		const nPuzzle::searchMode&	searchMode;
		mutable std::map<int32_t, int32_t>			heuristic;
		mutable std::map<int32_t, nPuzzle::Board>	pending;
		int32_t	cost = 0;
		int32_t	score = 0;
		nPuzzle::State *previous = nullptr;

	private:

		// Board getters
		bool	sameBoard(const State &rhs) const noexcept;

		// Moving Tiles
		void	increaseCost(void);

		// Solution
		void	addPendingHeuristic(int32_t h, const nPuzzle::Board& target) const;
		void	checkPendingHeuristic(int32_t h) const;

	public:
		State(const nPuzzle& puzzle);
		State(const State &src);
		~State(void);

		// Parsing
		void	addTile(const int32_t value, const int32_t x, const int32_t y);

		// Board getters
		int32_t	getPuzzleSize(void) const;
		int32_t	getPuzzleHeight(void) const;
		int32_t	getPuzzleWidth(void) const;
		const nPuzzle::Board&	getBoard() const;
		const nPuzzle::Board::Tile&	getTile(const int32_t value) const;
		const nPuzzle::Board::Tile&	getTile(const int32_t x, const int32_t y) const;
		const nPuzzle::Board::Tile&	getEmptyTile() const;

		// Moving Tiles
		bool	move(Direction direction);
		int32_t	getCost(void) const;

		// Calculation
		void	calculateAllHeuristics(const nPuzzle::Board& target);
		void	calculateOneHeuristic(const nPuzzle::Board& target);
		void	calculateOneHeuristic(const nPuzzle::Board& target, int32_t h) const;
		int32_t	getHeuristic(int32_t h) const;
		void	clearPendingHeuristics(void);

		// Solution
		void	setPrevious(nPuzzle::State *state);
		const nPuzzle::State*	getPrevious(void) const;

		// operator overloads
		State	&operator=(const State &src);
		bool	operator<(const State &rhs) const noexcept;
		bool	operator<=(const State &rhs) const noexcept;
		bool	operator>(const State &rhs) const noexcept;
		bool	operator>=(const State &rhs) const noexcept;

		friend std::ostream&	operator<<(std::ostream& os, const nPuzzle::State& state);
};

#endif
