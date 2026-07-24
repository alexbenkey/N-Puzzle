/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/07/24 16:19:03 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>	// std::abs()

#include "heuristic.hpp"
#include "nPuzzle.Board.hpp"
#include "nPuzzle.Board.Tile.hpp"

#include <iostream>

namespace
{
	int32_t	manhattan(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		int32_t	heuristic = 0;

		for (int32_t value = 1, size = target.getSize(); value < size; ++value)
		{
			const nPuzzle::Board::Tile&	currentTile = current.getTile(value);
			const nPuzzle::Board::Tile&	targetTile = target.getTile(value);
			heuristic += std::abs(currentTile.getX() - targetTile.getX());
			heuristic += std::abs(currentTile.getY() - targetTile.getY());
		}
		return (heuristic);
	}
	// int32_t	manhattan(const nPuzzle::State* current, const nPuzzle::State* target)
	// {
	// 	int32_t	heuristic = 0;

	// 	for (int32_t value = 1, size = target->getPuzzleSize(); value < size; ++value)
	// 	{
	// 		nPuzzle::Board::Tile	currentTile = current->getTile(value);
	// 		nPuzzle::Board::Tile	targetTile = target->getTile(value);
	// 		heuristic += std::abs(currentTile.getX() - targetTile.getX());
	// 		heuristic += std::abs(currentTile.getY() - targetTile.getY());
	// 	}
	// 	return (heuristic);
	// }

	int32_t	displaced(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		int32_t	heuristic = 0;

		for (int32_t value = 1, size = target.getSize(); value < size; ++value)
		{
			const nPuzzle::Board::Tile&	currentTile = current.getTile(value);
			const nPuzzle::Board::Tile&	targetTile = target.getTile(value);
			if (currentTile.getX() != targetTile.getX() || \
				currentTile.getY() != targetTile.getY())
				++heuristic;
		}
		return (heuristic);
	}
	// int32_t	displaced(const nPuzzle::State* current, const nPuzzle::State* target)
	// {
	// 	int32_t	heuristic = 0;

	// 	for (int32_t value = 1, size = target->getPuzzleSize(); value < size; ++value)
	// 	{
	// 		nPuzzle::Board::Tile	currentTile = current->getTile(value);
	// 		nPuzzle::Board::Tile	targetTile = target->getTile(value);
	// 		if (currentTile.getX() != targetTile.getX() || \
	// 			currentTile.getY() != targetTile.getY())
	// 			++heuristic;
	// 	}
	// 	return (heuristic);
	// }
}

namespace heuristic
{
	const List	function[] =
	{
		{ "Displaced", displaced },
		{ "Manhattan", manhattan },
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	getHeuristic(int32_t h, const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		if (h < 0 || h >= heuristic::size)
			return (-1);
		return (heuristic::function[h].f(current, target));
	}
}
