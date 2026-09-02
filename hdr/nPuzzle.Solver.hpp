/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:35:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/02 16:38:20 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_SOLVER_HPP
# define NPUZZLE_SOLVER_HPP

# include "nPuzzle.hpp"
# include "threadWorker.hpp"

# include <queue>	// std::priority_queue
# include <unordered_map>	// std::unordered_map
# include <vector>	// std::vector
# include <atomic>	// std::atomic

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
		const nPuzzle&	puzzle;
		const int32_t&	heuristicIndex;
		bool	calculateAllHeuristics;
		bool	solved;
#warning not sure how this interacts with mutexes
		std::atomic<nPuzzle::Solvability>	solvability{nPuzzle::Solvability::UNKNOWN};

		ThreadWorker	thread;

		std::priority_queue<nPuzzle::State*, std::vector<nPuzzle::State*>, StateCompare>	queue;
		std::unordered_map<const nPuzzle::Board*, nPuzzle::State*, BoardPtrHash, BoardPtrEqual>	visited;
		std::vector<nPuzzle::State*>	owner;

		void	setWorkerState(ThreadWorker::State state);
		ThreadWorker::State	getWorkerState(void) const;

		void	setCalculateAllHeuristics(bool all);
		bool	getCalculateAllHeuristics(void) const;

		void	solveStepWorker(void);
		void	processState(nPuzzle::State* state);
		void	addToQueue(nPuzzle::State* state);
		nPuzzle::State*	popQueue(void);

		void	determineIsSolved(void);
		void	setSolvability(nPuzzle::Solvability val);

	public:
		Solver(nPuzzle&	puzzle);
		~Solver(void);

		void	solve(void);
		bool	solveStep(bool calculateAllHeuristics = true);

		bool	isSolved(void);
		void	determineSolvability(void);
		nPuzzle::Solvability	getSolvability(void) const;

		size_t	getQueueSize(void) const;
		int32_t	getTopCost(void) const;
		int32_t	getTopHeuristic(void) const;
		const nPuzzle::State&	getTopState(void) const;
		std::vector<const nPuzzle::State*>	getSolution(void) const;

		void	clearQueue(void);
};

#endif
