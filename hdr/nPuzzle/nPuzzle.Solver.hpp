/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:35:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/03 19:13:24 by othello          ###   ########.fr       */
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

#warning not sure how this interacts with mutexes
		std::atomic<nPuzzle::Solvability>	solvability{nPuzzle::Solvability::UNKNOWN};

		const int32_t&	heuristicIndex;
		bool	calculateAllHeuristics;
		bool	solved;

		std::priority_queue<nPuzzle::State*, std::vector<nPuzzle::State*>, StateCompare>	queue;
		std::unordered_map<const nPuzzle::Board*, nPuzzle::State*, BoardPtrHash, BoardPtrEqual>	visited;
		std::vector<nPuzzle::State*>	owner;

		ThreadWorker	thread;

		// Solvability
		void	setSolvability(nPuzzle::Solvability val);

		// Solving
		void	setCalculateAllHeuristics(bool all);
		bool	getCalculateAllHeuristics(void) const;
		void	solveStepWorker(void); // Inside thread
		void	processState(nPuzzle::State* state);
		void	determineIsSolved(void);

		// Queue
		void	addToQueue(nPuzzle::State* state);
		nPuzzle::State*	popQueue(void);

		// Thread
		void	setWorkerState(ThreadWorker::State state);
		ThreadWorker::State	getWorkerState(void) const;

	public:
		Solver(nPuzzle&	puzzle);
		~Solver(void);

		// Solvability
		void	determineSolvability(void);
		nPuzzle::Solvability	getSolvability(void) const;

		// Solving
		void	solve(void);
		bool	solveStep(bool calculateAllHeuristics = true);
		bool	isSolved(void);
		std::vector<const nPuzzle::State*>	getSolution(void) const;

		// Queue
		size_t	getQueueSize(void) const;
		const nPuzzle::State&	getTopState(void) const;
		int32_t	getTopHeuristic(void) const;
		int32_t	getTopCost(void) const;
		void	clearQueue(void);
};

#endif
