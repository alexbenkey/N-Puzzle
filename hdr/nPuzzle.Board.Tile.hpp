/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Board.Tile.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:27:40 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:37:19 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_BOARD_TILE_HPP
# define NPUZZLE_BOARD_TILE_HPP

# include "nPuzzle.Board.hpp"

class nPuzzle::Board::Tile
{
	private:
		int32_t	value;
		int32_t	x;
		int32_t	y;

	public:
		Tile(const int32_t value, const int32_t x, const int32_t y);
		~Tile();

		void			setVal(const int32_t val);
		const int32_t	getVal(void) const;
		void			setX(const int32_t val);
		const int32_t	getX(void) const;
		void			setY(const int32_t val);
		const int32_t	getY(void) const;

		void	swapCoords(Tile& other);
		friend std::ostream&	operator<<(std::ostream& os, const nPuzzle::Board::Tile& tile);
};

#endif
