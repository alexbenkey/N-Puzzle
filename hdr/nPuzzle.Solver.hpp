/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Solver.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:35:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/30 14:05:22 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_SOLVER_HPP
# define NPUZZLE_SOLVER_HPP

# include "nPuzzle.hpp"

# include <vector>	// std::vector
# include <mutex>	// std::mutex

class nPuzzle::Solver
{
	private:
		nPuzzle&	puzzle;
		int32_t		heuristic;
		std::vector<nPuzzle::State*>	queue;
		int32_t							queueIndex;
		mutable std::mutex				queueMutex;
		std::vector<nPuzzle::State*>	visited;

		// bool	solveStep_mtx(bool calculateAllHeuristics = true);
		void	processState(nPuzzle::State* state, bool calculateAllHeuristics);
		bool	stateHasAlreadyBeenVisited(nPuzzle::State* state);
		bool	stateIsAlreadyInQueue(nPuzzle::State* state);

		void	addToQueue(nPuzzle::State* state);
		nPuzzle::State*	popQueue(void);


		void	maintainValidQueueIndex(void);

	public:
		Solver(nPuzzle&	puzzle);
		~Solver(void);

		bool	solve(void);
		bool	solveStep(bool calculateAllHeuristics = true);

		size_t	getQueueSize(void) const;
		void	incrementQueueIndex(void);
		void	decrementQueueIndex(void);
		int32_t	getQueueIndex(void) const;
		const nPuzzle::State&	getQueueMember(int32_t i = 0) const;
		int32_t	getBestHeuristic(void) const;
		bool	isSolved(void) const;
		std::vector<const nPuzzle::State*>	getSolution(void) const;

		void	printQueueStatus(void) const;
		void	printQueueNodeStatus(const nPuzzle::State* state) const;

		void	clearQueue(void);
		void	clearVisited(void);
};

#endif
