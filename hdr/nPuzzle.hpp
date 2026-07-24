/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:41:42 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/24 14:43:56 by ohengelm         ###   ########.fr       */
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
# pragma endregion "Nested Objects"

# pragma region	"Enum Classes"
		enum class Direction
		{ 
			UP, 
			RIGHT,
			DOWN,
			LEFT
		};
# pragma endregion

	private:
		int32_t	width;
		int32_t	height;
		int32_t	size;
		nPuzzle::State*		start;
		nPuzzle::State*		state;
		nPuzzle::Target*	target;

		std::vector<nPuzzle::State*>	queue;
		int32_t							queueIndex = -1;
		std::vector<nPuzzle::State*>	visited;

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
		void		clearProgress(void);
		void			clearQueue(void);
		void			clearVisited(void);
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

		nPuzzle::State&	getCurrentState()	{ return (*this->state); }
		// nPuzzle::State&	getTargetState()	{ return (*(nPuzzle::State*)this->target); }
		nPuzzle::Target&	getTarget() const { return (*this->target); }
		nPuzzle::State&	getStartState()		{ return (*this->start); }
		nPuzzle::State&	getQueueState(void);
		void	incrementQueue(void)	{ ++this->queueIndex; this->maintainValidQueue(); }
		void	decrementQueue(void)	{ --this->queueIndex; this->maintainValidQueue(); }
		void	maintainValidQueue(void);
		int32_t	getQueueIndex(void) const	{ return (this->queueIndex); }
		int32_t getQueueSize(void) const { return (this->queue.size()); }

		void	storeStartState(void) { this->start = this->state; }

		void	printPuzzle(void);
		void	printTarget(void);
		void	printQueue(void);
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
	
		void	solve(int32_t h);
		void	solveStep(int32_t h = -1);
		void	processState(nPuzzle::State* state, int32_t h);
		bool	stateHasAlreadyBeenVisited(nPuzzle::State* state);
		bool	stateIsAlreadyInQueue(nPuzzle::State* state);
		void	calculateHeuristic(void);
		void	calculateHeuristic(int32_t h);

		nPuzzle	&operator=(const nPuzzle &src);
};

#endif
