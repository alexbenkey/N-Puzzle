/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:35:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/10 20:10:45 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_SOLVER_HPP
# define NPUZZLE_SOLVER_HPP

# include "nPuzzle.hpp"

# include <thread>	// std::thread
# include <mutex>	// std::mutex
# include <condition_variable>	// std::condition_variable

# include <queue>	// std::priority_queue
# include <unordered_map>	// std::unordered_map
# include <vector>	// std::vector
# include <mutex>	// std::mutex
# include <atomic>	// std::atomic

enum WorkerState
{
	STOP,
	IDLE,
	RUNONE,
	RUNALL,
};

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

		std::thread				worker;
		mutable std::mutex		mutex;
		WorkerState				workerState;
		std::condition_variable	workerCondition;

		std::priority_queue<nPuzzle::State*, std::vector<nPuzzle::State*>, StateCompare>	queue;
		std::unordered_map<const nPuzzle::Board*, nPuzzle::State*, BoardPtrHash, BoardPtrEqual>	visited;
		std::vector<nPuzzle::State*>	owner;

		void	setWorkerState(WorkerState state);
		WorkerState	getWorkerState(void) const;
		void	ensureActiveWorker(void);
		void	stopWorker(void);

		void	setCalculateAllHeuristics(bool all);
		bool	getCalculateAllHeuristics(void) const;

		void	solveWorker(void);
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
