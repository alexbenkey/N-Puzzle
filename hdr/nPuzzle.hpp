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
		const int32_t		width;
		const int32_t		height;
		const int32_t		size;
		nPuzzleTarget	target;
		nPuzzleState	state;

	protected:

	public:
		nPuzzle(const int32_t size);
		nPuzzle(const int32_t width, const int32_t height);
		nPuzzle(const nPuzzle &src);
		~nPuzzle(void);

		void	setRow(int32_t row, const std::vector<int>& numbers);

		void	printPuzzle(void) { this->state.printPuzzle(); }
		void	printTarget(void) { this->target.printPuzzle(); }
		void	printEmptyTilePos(void) {this->state.printTilePos( this->state.getTile(0)); }

		void moveUp(void) { this->state.moveUp(); }
		void moveDown(void) { this->state.moveDown(); }
		void moveLeft(void) { this->state.moveLeft(); }
		void moveRight(void) { this->state.moveRight(); }

		nPuzzle	&operator=(const nPuzzle &src);
};

#endif

