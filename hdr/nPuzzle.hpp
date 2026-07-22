/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzle.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include "nPuzzleState.hpp"
# include "nPuzzleTarget.hpp"

# include <vector>

class nPuzzle
{
	private:
		const int32_t	width;
		const int32_t	height;
		const int32_t	size;
		nPuzzleState	start;
		nPuzzleTarget	target;
		nPuzzleState	state;

		std::vector<nPuzzleState*>	queue;
		int32_t						queueIndex = -1;
		std::vector<nPuzzleState*>	visited;

		bool	move(nPuzzleState::Direction direction, int32_t h);

	protected:

	public:
		// nPuzzle(void); 
		nPuzzle(const int32_t size);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		void	resetStates(void);
		void	clearStates(void);
		void	setRow(int32_t row, const std::vector<int>& numbers);

		nPuzzleState&	getCurrentState()	{ return (this->state); }
		nPuzzleState&	getTargetState()	{ return (this->target); }
		nPuzzleState&	getStartState()		{ return (this->start); }
		nPuzzleState&	getQueueState(void);
		void	incrementQueue(void)	{ ++this->queueIndex; this->maintainValidQueue(); }
		void	decrementQueue(void)	{ --this->queueIndex; this->maintainValidQueue(); }
		void	maintainValidQueue(void);
		int32_t	getQueueIndex(void) const	{ return (this->queueIndex); }
		int32_t getQueueSize(void) const { return (this->queue.size()); }

		void	storeStartState(void) { this->start = this->state; }

		void	printPuzzle(void) { this->state.printPuzzle(); }
		void	printTarget(void) { this->target.printPuzzle(); }
		void	printQueue(void)	{ if (this->queue.size()) this->queue[this->queueIndex]->printPuzzle(); }
		void	printEmptyTilePos(void) {this->state.printTilePos( this->state.getTile(0)); }
		void	printAllTiles(const nPuzzleState& state) const;
		void	printAllTilesFlex(nPuzzleState& state);

		int32_t getWidth(void) const { return this->width; }
		int32_t getHeight(void) const { return this->height; }
		int32_t getSize(void) const { return this->size; }

		bool	moveUp(int32_t h = -1)	{ return(this->move(nPuzzleState::Direction::UP, h)); }
		bool	moveDown(int32_t h = -1)	{ return(this->move(nPuzzleState::Direction::DOWN, h)); }
		bool	moveLeft(int32_t h = -1)	{ return(this->move(nPuzzleState::Direction::LEFT, h)); }
		bool	moveRight(int32_t h = -1)	{ return(this->move(nPuzzleState::Direction::RIGHT, h)); }
	
		void	solve(int32_t h);
		void	solveStep(int32_t h = -1);
		void	processState(nPuzzleState* state, int32_t h);
		bool	stateHasAlreadyBeenVisited(nPuzzleState* state);
		bool	stateIsAlreadyInQueue(nPuzzleState* state);
		void	calculateHeuristic(void);
		void	calculateHeuristic(int32_t h);

		nPuzzle	&operator=(const nPuzzle &src);
};

#endif

