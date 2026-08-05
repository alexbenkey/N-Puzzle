/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.Board.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:27:40 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/31 17:35:34 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_BOARD_HPP
# define NPUZZLE_BOARD_HPP

# include "nPuzzle.hpp"
// class nPuzzle
// {
// 	public:
// 		class Board;
// };

# include <memory>	// std::unique_ptr
# include <vector>	// std::vector
# include <stdexcept>	// std::exception

class nPuzzle::Board
{
# pragma region "Nested Objects"
	public:
		class	Tile;
# pragma endregion "Nested Objects"

	private:
		int32_t	width;
		int32_t	height;
		int32_t	size;
		std::vector<std::unique_ptr<Tile>>	TilesByVal;
		std::vector<Tile*>					TilesByPos;

	public:
		Board();
		Board(const Board& src);
		~Board();

		void	setSize(const int32_t w, const int32_t h);
		const int32_t	getWidth(void) const;
		const int32_t	getHeight(void) const;
		const int32_t	getSize(void) const;

		const Tile&	getTile(const int32_t value) const;
		const Tile&	getTile(const int32_t x, const int32_t y) const;
		const Tile& getEmptyTile(void) const;

		void	addTile(const int32_t value, const int32_t x, const int32_t y);
		bool	move(nPuzzle::Direction direction);
		void	swapTiles(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2);

		void	clearTiles(void);

		nPuzzle::Board&	operator=(const Board& src);
		bool	operator==(const Board& ref) const;
		std::size_t	hash() const;

		friend std::ostream&	operator<<(std::ostream& os, const Board& board);
};

struct BoardHash
{
    std::size_t operator()(const nPuzzle::Board& board) const noexcept
    {
        return board.hash();
    }
};

struct BoardEqual
{
    bool operator()(const nPuzzle::Board& lhs,
                    const nPuzzle::Board& rhs) const noexcept
    {
        return lhs == rhs;
    }
};

#endif
