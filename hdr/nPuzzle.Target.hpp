/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Target.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:45:10 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/24 14:38:45 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_TARGET_HPP
# define NPUZZLE_TARGET_HPP

# include "nPuzzle.hpp"
# include "nPuzzle.Board.hpp"

class nPuzzle::Target
{
	private:
		Board	board;
		void	setTargetTiles(void);

	protected:

	public:
		Target(void);
		Target(const int32_t width, const int32_t height);
		Target(const Target& src);

		void	setSize(const int32_t w, const int32_t h);

		const Board&	getBoard(void) const;

		nPuzzle::Target&	operator=(const nPuzzle::Target &src);
		friend std::ostream&	operator<<(std::ostream& os, const nPuzzle::Target& state);

};

#endif
