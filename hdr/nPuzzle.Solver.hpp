/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:35:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/30 19:49:09 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_SOLVER_HPP
# define NPUZZLE_SOLVER_HPP

# include "nPuzzle.hpp"

# include <queue>	// std::priority_queue
# include <unordered_map>	// std::unordered_map
# include <vector>	// std::vector
# include <mutex>	// std::mutex

#pragma region "Comparator functions for contain sorting"
struct BoardPtrHash
{
	std::size_t	operator()(const nPuzzle::Board* board) const noexcept;
};

struct BoardPtrEqual
{
	bool	operator()(const nPuzzle::Board* lhs, const nPuzzle::Board* rhs) const noexcept;
};

struct StateCompare
{
	bool	operator()(const nPuzzle::State* a, const nPuzzle::State* b) const;
};
#pragma endregion

class nPuzzle::Solver
{
	private:
		nPuzzle&	puzzle;
		int32_t		heuristic;
		std::priority_queue<nPuzzle::State*, std::vector<nPuzzle::State*>, StateCompare>	queue;
		std::unordered_map<const nPuzzle::Board*, nPuzzle::State*, BoardPtrHash, BoardPtrEqual>	visited;
		std::vector<nPuzzle::State*>	owner;
		mutable std::mutex				queueMutex;

		void	processState(nPuzzle::State* state, bool calculateAllHeuristics);

		void	addToQueue(nPuzzle::State* state);
		nPuzzle::State*	popQueue(void);

	public:
		Solver(nPuzzle&	puzzle);
		~Solver(void);

		bool	solve(void);
		bool	solveStep(bool calculateAllHeuristics = true);

		size_t	getQueueSize(void) const;
		const nPuzzle::State&	getTopState(void) const;
		int32_t	getTopCost(void) const;
		int32_t getTopHeuristic(void) const;
		bool	isSolved(void) const;
		void	getSolution(void) const;

		void	printQueueStatus(void) const;

		void	clearQueue(void);

		void	debugValidateQueueVisited(void);
};

#endif
