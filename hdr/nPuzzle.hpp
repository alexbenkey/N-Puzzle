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

#include "nPuzzleState.hpp"
#include "nPuzzleTarget.hpp"

class nPuzzle
{
	private:
		const int32_t	width;
		const int32_t	height;
		const int32_t	size;
		nPuzzleState	start;
		nPuzzleTarget	target;
		nPuzzleState	state;

	protected:

	public:
		// nPuzzle(void); 
		nPuzzle(const int32_t size);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		void	setRow(int32_t row, const std::vector<int>& numbers);

		// int	getWidth() const	{ return (this->width); }
		// int	getHeight() const	{ return (this->height); }
		// int	getSurface() const	{ return (this->width * this->height); }

		nPuzzleState&	getCurrentState()	{ return (this->state); }
		nPuzzleState&	getTargetState()	{ return (this->target); }
		nPuzzleState&	getStartState()		{ return (this->start); }
		void	storeStartState(void) { this->start = this->state; }

		void	printPuzzle(void) { this->state.printPuzzle(); }
		void	printTarget(void) { this->target.printPuzzle(); }
		void	printEmptyTilePos(void) {this->state.printTilePos( this->state.getTile(0)); }

		int32_t getWidth(void) const { return this->width; }
		int32_t getHeight(void) const { return this->height; }
		int32_t getSize(void) const { return this->size; }

		void moveUp(void) { this->state.moveUp(); }
		void moveDown(void) { this->state.moveDown(); }
		void moveLeft(void) { this->state.moveLeft(); }
		void moveRight(void) { this->state.moveRight(); }

		nPuzzle	&operator=(const nPuzzle &src);
};

#endif

