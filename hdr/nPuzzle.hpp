/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:41:42 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:46:42 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <vector>	// std::vector
# include <string>	// std::string std::getline() std::istream
# include <sstream>	// std::istringstream

class nPuzzle
{
# pragma region "Nested Classes"
	public:
		class	Board;
		class	State;
		class	Target;
# pragma endregion "Nested Classes"

# pragma region	"Enum Classes"
		enum class Direction { 
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
		nPuzzle::State*	start;
		nPuzzle::Target*	target;
		nPuzzle::State*	state;

		std::vector<nPuzzle::State*>	queue;
		int32_t						queueIndex = -1;
		std::vector<nPuzzle::State*>	visited;

		// Parsing
		bool	emptyLine(const std::string& line) const;
		bool	validLine(const std::string& line) const;
		static std::vector<int>	convertLineToNumbers(const std::string& line);
		void	setRow(int32_t row, const std::vector<int>& numbers);

		// Movement
		bool	move(nPuzzle::Direction direction, int32_t h);

	protected:

	public:
		nPuzzle(void);
		nPuzzle(std::istream& __is);
		nPuzzle(const int32_t size);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		void	parse(std::istream& __is);
		void	resetStates(void);
		void	clearStates(void);

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

		bool	moveUp(int32_t h = -1)	{ return(this->move(nPuzzle::Direction::UP, h)); }
		bool	moveDown(int32_t h = -1)	{ return(this->move(nPuzzle::Direction::DOWN, h)); }
		bool	moveLeft(int32_t h = -1)	{ return(this->move(nPuzzle::Direction::LEFT, h)); }
		bool	moveRight(int32_t h = -1)	{ return(this->move(nPuzzle::Direction::RIGHT, h)); }
	
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
