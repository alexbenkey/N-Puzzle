/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/07/14 18:04:00 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>	// std::abs()

#include "heuristic.hpp"
#include <iostream>

namespace heuristic
{
	const List	function[] =
	{
		{ "Displaced", displaced },
		{ "Manhattan", manhattan },
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	manhattan(const nPuzzleState* current, const nPuzzleState* target)
	{
		int32_t	heuristic = 0;

		for (int32_t value = 1, size = target->getPuzzleSize(); value < size; ++value)
		{
			nPuzzleState::Tile	currentTile = current->getTile(value);
			nPuzzleState::Tile	targetTile = target->getTile(value);
			heuristic += std::abs(currentTile.getxPos() - targetTile.getxPos());
			heuristic += std::abs(currentTile.getyPos() - targetTile.getyPos());
		}
		return (heuristic);
	}

	int32_t	displaced(const nPuzzleState* current, const nPuzzleState* target)
	{
		int32_t	heuristic = 0;

		for (int32_t value = 1, size = target->getPuzzleSize(); value < size; ++value)
		{
			nPuzzleState::Tile	currentTile = current->getTile(value);
			nPuzzleState::Tile	targetTile = target->getTile(value);
			if (currentTile.getxPos() != targetTile.getxPos() || \
				currentTile.getyPos() != targetTile.getyPos())
				++heuristic;
		}
		return (heuristic);
	}
}
