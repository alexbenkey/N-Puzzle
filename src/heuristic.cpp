/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/07/31 17:03:52 by avon-ben         ###   ########.fr       */
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
	// int32_t walkingDistance(const nPuzzle::Board& current, const nPuzzle::Board& target)
	// {
	// 	int32_t heuristic = 0;
		

	// }
	int32_t LinearConflicts(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		int32_t heuristic = manhattan(current, target);
		std::vector<int32_t> foundConflicts(current.getSize(), 0);

		//Columns
		for (int32_t x = 0; x < current.getWidth(); ++x)
		{
			for (int32_t y_1 = 0; y_1 < current.getHeight(); ++y_1)
			{
				const int32_t val1 = current.getTile(x, y_1).getVal();

				// if there are multiple conflicts in the same row, the heuristic value does not increase further
				if (val1 == 0 || foundConflicts[val1] != 0)
					continue;

				const nPuzzle::Board::Tile &T1 = target.getTile(val1);
				if (T1.getX() != x)
					continue;

				for (int32_t y_2 = y_1 + 1; y_2 < target.getHeight(); ++ y_2)
				{
					const int32_t val2 = current.getTile(x, y_2).getVal();
					
					if (val2 == 0 || foundConflicts[val2] != 0 )
						continue;
						
					const nPuzzle::Board::Tile &T2 = target.getTile(val2);
					if (T2.getX() == x && T1.getY() > T2.getY())
					{
						++foundConflicts[T1.getVal()];
						++foundConflicts[T2.getVal()];
						break ;
					}
				}
			}
		}

		//Rows
		for (int32_t y = 0; y < current.getHeight(); ++y)
		{
			for (int32_t x_1 = 0; x_1 < current.getWidth(); ++x_1)
			{
				const int32_t val1 = current.getTile(x_1, y).getVal();

				if (val1 == 0 || foundConflicts[val1] != 0)
					continue;
				
				const nPuzzle::Board::Tile &T1 = target.getTile(val1);
				if (T1.getY() != y)
					continue;
				
				for (int32_t x_2 = x_1 + 1; x_2 < current.getWidth(); ++x_2)
				{ 
					const int32_t val2 = current.getTile(x_2, y).getVal();

					if (val2 == 0 || foundConflicts[val2] != 0)
						continue;

					const nPuzzle::Board::Tile &T2 = target.getTile(val2);
					if (T2.getY() == y && T1.getX() > T2.getX())
					{
						++foundConflicts[T1.getVal()];
						++foundConflicts[T2.getVal()];
						break;
					}
				}
			}

		}
	for (int32_t i : foundConflicts)
		heuristic += i;
	
	return (heuristic);

	}
}

namespace heuristic
{
	const List	function[] =
	{
		{ "Displaced", displaced },
		{ "Manhattan", manhattan },
		{ "Linear Conflicts", LinearConflicts}
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	getHeuristic(int32_t h, const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		if (h < 0 || h >= heuristic::size)
			return (-1);
		return (heuristic::function[h].f(current, target));
	}
}
