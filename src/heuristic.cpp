/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/07/14 15:07:00 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>	// std::abs()

#include "heuristic.hpp"
#include <iostream>

namespace heuristic
{
	const List	function[] =
	{
		{ "Manhattan", manhattan },
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	manhattan(const nPuzzleState* current, const nPuzzleState* target)
	{
		int32_t	heuristic = 0;

		for (int32_t value = 1, size = target->getPuzzleSize(); value < size; ++value)
		{
			nPuzzleState::Tile	currentTile = current->getTile(value);
			nPuzzleState::Tile	targetTile = current->getTile(value);
			heuristic += std::abs(currentTile.getxPos() - targetTile.getxPos());
			heuristic += std::abs(currentTile.getyPos() - targetTile.getyPos());
		}

		// for (int32_t x = 0, width = target->getPuzzleWidth(); x < width; ++x)
		// {
		// 	for (int32_t y = 0, height = target->getPuzzleHeight(); y < height; ++y)
		// 	{
		// 		int32_t	value = current->getTile(x, y).getVal();
		// 		if (value <= 0)
		// 			continue;
		// 		nPuzzleState::Tile	targetTile = target->getTile(value);
		// 		// if (targetTile.getVal() != value)
		// 		// 	std::cerr << value << " != " << targetTile.getVal()	<< std::endl;
		// 		// if (!(x == targetTile.getxPos() && y == targetTile.getyPos()))
		// 		// 	std::cerr << value	<< ": ["	<< x	<< "][" << y	<< "]\t[" << targetTile.getxPos() << "][" << targetTile.getyPos() << "]"<< std::endl;
		// 		// target->printTilePos(targetTile);
		// 		heuristic += std::abs(x - targetTile.getxPos());
		// 		heuristic += std::abs(y - targetTile.getyPos());
		// 	}
		// }
		return (heuristic);
	}
}
