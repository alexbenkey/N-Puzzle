/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:41:42 by ohengelm          #+#    #+#             */
/*   Updated: 2026/08/06 19:33:24 by avon-ben         ###   ########.fr       */
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

# pragma region	"Enum Classes"
		enum class Direction
		{ 
			UP, 
			RIGHT,
			DOWN,
			LEFT
		};

		enum class searchMode
		{
			ASTAR,
			GREEDY,
			UNIFORM
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

		nPuzzle::searchMode mode = nPuzzle::searchMode::ASTAR;
		int32_t		heuristicIndex = 1;

		// Construction
		void	setVariables(const int32_t width, const int32_t height);
		// Parsing
		bool	emptyLine(const std::string& line) const;
		bool	validLine(const std::string& line) const;
		static std::vector<int>	convertLineToNumbers(const std::string& line);
		void	setRow(int32_t row, const std::vector<int>& numbers);

		// Movement
		bool	move(nPuzzle::Direction direction, int32_t h);

		// Deletion
		void	clearAll(void);
		void		clearSolver(void);
		void		clearBoard(void);
		void			clearState(nPuzzle::State** state);
		void			clearTarget(void);

	protected:

	public:

		nPuzzle(void);
		nPuzzle(std::istream& __is);
		nPuzzle(const int32_t widthAndHeight);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		void	parse(std::istream& __is);
		void	resetToStart(void);

		nPuzzle::Solvability getSolvability(void) const;

		nPuzzle::State&		getCurrentState()	{ return (*this->state); }
		nPuzzle::Target&	getTarget() const { return (*this->target); }
		nPuzzle::State&		getStartState()		{ return (*this->start); }
		const nPuzzle::State&	getQueueState(void);
		void	incrementHeuristic(void);
		void	decrementHeuristic(void);
		void	maintainValidHeuristic(void);
		int32_t	getHeuristicIndex(void) const;
		int32_t	getQueueSize(void) const;

		void	storeStartState(void);

		void	setSearchMode(nPuzzle::searchMode mode);
		nPuzzle::searchMode getSearchMode(void) {return this->mode; }

		void	printPuzzle(void);
		void	printTarget(void);
		void	printQueue(void);
		void	printQueueStatus(const nPuzzle::State& queue, int32_t h);
		std::vector<const nPuzzle::State*> getSolution(void) const;
		// void	printEmptyTilePos(void);
		// void	printAllTiles(const nPuzzle::State& state) const;
		// void	printAllTilesFlex(nPuzzle::State& state);

		int32_t getWidth(void) const { return this->width; }
		int32_t getHeight(void) const { return this->height; }
		int32_t getSize(void) const { return this->size; }

		bool	moveUp(int32_t h = -1);
		bool	moveDown(int32_t h = -1);
		bool	moveLeft(int32_t h = -1);
		bool	moveRight(int32_t h = -1);
	
		void	solve(void);
		bool	solveStep(bool allHeuristics = false);
		int32_t	getBestSolverHeuristic(void) const;
		bool	isSolved(void) const;
		void	calculateHeuristic(void);
		void	calculateHeuristic(int32_t h);

		nPuzzle	&operator=(const nPuzzle &src);
};

#endif
