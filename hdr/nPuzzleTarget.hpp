/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nPuzzleTarget.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/12 16:13:50 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/06/12 16:13:50 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLETARGET_HPP
# define NPUZZLETARGET_HPP

# include "nPuzzleState.hpp"

class nPuzzleTarget: public nPuzzleState
{
	private:
		void	setTargetTiles(void);

	protected:

	public:
		nPuzzleTarget(const int32_t width, const int32_t height);
};

#endif
