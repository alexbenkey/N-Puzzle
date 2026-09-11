/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:41:42 by ohengelm          #+#    #+#             */
/*   Updated: 2026/09/03 20:41:47 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <vector>	// std::vector
# include <string>	// std::string std::getline() std::istream
# include <sstream>	// std::istringstream

class nPuzzle
{
# pragma region "Nested Objects"
	public:
		class	Board;
		class	State;
		class	Target;
		class	Solver;
# pragma endregion "Nested Objects"

# pragma region "Enum Classes"
		enum class Direction
		{
			UP,
			RIGHT,
			DOWN,
			LEFT
		};

		enum class searchMode
		{
			GREEDY,
			ASTAR,
			UNIFORM,
			size
		};

		enum class Solvability
		{
			UNKNOWN,
			SOLVABLE,
			UNSOLVABLE
		};
# pragma endregion

	private:
		int32_t	width;
		int32_t	height;
		int32_t	size;

		nPuzzle::State*		start;
		nPuzzle::State*		state;
		nPuzzle::Target*	target;
		nPuzzle::Solver*	solver;

		nPuzzle::searchMode	mode = nPuzzle::searchMode::ASTAR;
		int32_t				heuristicIndex = 1;

		// Construction
		void	setVariables(const int32_t width, const int32_t height);

		// Parsing
		bool	emptyLine(const std::string& line) const;
		bool	validLine(const std::string& line) const;
		static std::vector<int>	convertLineToNumbers(const std::string& line);
		void	setRow(int32_t row, const std::vector<int>& numbers);
		void	storeStartState(void);

		// Movement
		bool	move(nPuzzle::Direction direction);

		// Deletion
		void	clearAll(void);
		void		clearSolver(void);
		void		clearBoard(void);
		void			clearState(nPuzzle::State** state);
		void			clearTarget(void);

		// Debug
		void	printPuzzle(void);
		void	printTarget(void);
		// void	printQueue(void);
		// void	printQueueStatus(const nPuzzle::State& queue, int32_t h);

	public:
		nPuzzle(void);
		nPuzzle(std::istream& __is);
		nPuzzle(const int32_t widthAndHeight);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		// Parsing
		void	parse(std::istream& __is);

		// Getters
		int32_t	getWidth(void) const;
		int32_t	getHeight(void) const;
		int32_t	getSize(void) const;
		const nPuzzle::State&	getCurrentState() const;
		const nPuzzle::Target&	getTarget() const;
		const nPuzzle::State&	getStartState()	const;
		const nPuzzle::State&	getQueueState(void);
		int32_t	getQueueSize(void) const;

		// Movement
		bool	moveUp(void);
		bool	moveDown(void);
		bool	moveLeft(void);
		bool	moveRight(void);

		// Search Mode
		void	setSearchMode(nPuzzle::searchMode mode);
		nPuzzle::searchMode	getSearchMode(void);
		void	incrementSearchMode(void);
		void	decrementSearchMode(void);

		// Heuristics
		void	setHeuristicIndex(int32_t index);
		int32_t	getHeuristicIndex(void) const;
		void	incrementHeuristicIndex(void);
		void	decrementHeuristicIndex(void);
		int32_t	getBestSolverHeuristic(void) const;

		// Solving
		nPuzzle::Solvability	getSolvability(void) const;
		void	solve(void);
		bool	solveStep(bool allHeuristics = false);
		bool	isSolved(void) const;
		std::vector<const nPuzzle::State*>	getSolution(void) const;

		// Reset
		void	resetToStart(void);

		// Operator overload
		nPuzzle	&operator=(const nPuzzle &src);
};

#endif
