/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/08/06 16:06:29 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Manhattan
#include <cmath>	// std::abs()
// Walking Distance
#include <queue>	// std::queue
#include <map>		// std::map
#include <mutex>	// std::mutex
#include <stdexcept>	// std::runtime_error

#include <iostream>	// std::stream

#include "heuristic.hpp"
#include "nPuzzle.Board.hpp"
#include "nPuzzle.Board.Tile.hpp"

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

	class WalkingDistanceClass
	{
		private:
			struct abstractKey
			{
				std::vector<int16_t>	counts;
				int32_t					blankLine;

				bool	operator<(const abstractKey& other) const
				{
					if (this->blankLine != other.blankLine)
						return this->blankLine < other.blankLine;
					return this->counts < other.counts;
				}
			};

			struct lookupTable
			{
				std::queue<abstractKey>				queue;
				std::map<abstractKey, int32_t>		distance;
				const int32_t	(nPuzzle::Board::Tile::*getCoord)() const;
				int32_t							lineCount;
			};

			int32_t		width;
			int32_t		height;
			int32_t		size;
			std::size_t	targetHash;
			lookupTable	row;
			lookupTable	col;
			std::mutex	lookupMutex;

			void	resetLookupTable(const nPuzzle::Board& target);
			int32_t	lookupHeuristicHalf(const nPuzzle::Board& current, const nPuzzle::Board& target, lookupTable& table);
			abstractKey	generateKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const lookupTable& table) const;
			int32_t	expandLookupTable(lookupTable& table, const abstractKey& key);

		public:
			WalkingDistanceClass(void);

			int32_t	lookupHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target);
	};

	WalkingDistanceClass::WalkingDistanceClass(void)
	{
		this->width = -1;
		this->height = -1;
		this->size = -1;
		this->targetHash = 0;
		this->row.getCoord = &nPuzzle::Board::Tile::getY;
		this->col.getCoord = &nPuzzle::Board::Tile::getX;
	}

	int32_t	WalkingDistanceClass::lookupHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		std::lock_guard<std::mutex>	lock(this->lookupMutex);

		if (this->width != target.getWidth() ||
			this->height != target.getHeight() ||
			this->targetHash != target.hash())
			resetLookupTable(target);

		int32_t	rowH = this->lookupHeuristicHalf(current, target, this->row);
		if (rowH < 0)
			throw std::runtime_error("Walking Distance row key was not found");
		
		int32_t	colH = this->lookupHeuristicHalf(current, target, this->col);
		if (colH < 0)
			throw std::runtime_error("Walking Distance column key was not found");

		return (rowH + colH);
	}

	int32_t	WalkingDistanceClass::lookupHeuristicHalf(const nPuzzle::Board& current, const nPuzzle::Board& target, lookupTable& table)
	{
		abstractKey	currentKey = this->generateKey(current, target, table);
		std::map<abstractKey, int32_t>::iterator found = table.distance.find(currentKey);
		if (found != table.distance.end())
			return (found->second);
		return (this->expandLookupTable(table, currentKey));
	}

	void	WalkingDistanceClass::resetLookupTable(const nPuzzle::Board& target)
	{
		this->width = target.getWidth();
		this->height = target.getHeight();
		this->size = this->width * this->height;
		this->targetHash = target.hash();

		this->row.lineCount = this->height;
		this->col.lineCount = this->width;

		{
			this->row.distance.clear();
			this->row.queue = {};
			abstractKey	goal = generateKey(target, target, this->row);
			this->row.distance.emplace(goal, 0);
			this->row.queue.push(goal);
		}
		{
			this->col.distance.clear();
			this->col.queue = {};
			abstractKey	goal = generateKey(target, target, this->col);
			this->col.distance.emplace(goal, 0);
			this->col.queue.push(goal);
		}
	}

	WalkingDistanceClass::abstractKey	WalkingDistanceClass::generateKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const lookupTable& table) const
	{
		abstractKey	key;
		key.counts.assign(table.lineCount * table.lineCount, 0);
		key.blankLine = (current.getEmptyTile().*table.getCoord)();

		for (int32_t value = 1; value < this->size; ++value)
		{
			int32_t	currentLine = (current.getTile(value).*table.getCoord)();
			int32_t	targetLine = (target.getTile(value).*table.getCoord)();
			++key.counts[currentLine * table.lineCount + targetLine];
		}
		return (key);
	}

	int32_t	WalkingDistanceClass::expandLookupTable(lookupTable& table, const abstractKey& key)
	{
		while (!table.queue.empty())
		{
			abstractKey	current = table.queue.front();
			table.queue.pop();
			int32_t	currentDepth = table.distance.at(current);

			for (int32_t sourceLine : { current.blankLine - 1, current.blankLine + 1 })
			{
				if (sourceLine < 0 || sourceLine >= table.lineCount)
					continue;

				for (int32_t targetGroup = 0; targetGroup < table.lineCount; ++targetGroup)
				{
					int32_t	sourceIndex = sourceLine * table.lineCount + targetGroup;
					if (current.counts[sourceIndex] == 0)
						continue;

					abstractKey	next = current;
					int32_t	destinationIndex = current.blankLine * table.lineCount + targetGroup;
					--next.counts[sourceIndex];
					++next.counts[destinationIndex];
					next.blankLine = sourceLine;

					if (table.distance.emplace(next, currentDepth + 1).second)
						table.queue.push(next);
				}
			}

			// Keep lazy BFS nodes expandable for later lookups. Returning before
			// this expansion would remove the requested node from the frontier.
			if (!(current < key) && !(key < current))
				return (currentDepth);
		}
		return (-1);
	}

	int32_t	walkingDistance(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		static WalkingDistanceClass	walkingDistance;

		return (walkingDistance.lookupHeuristic(current, target));
	}
}

namespace heuristic
{
	const List	function[] =
	{
		{ "Displaced", displaced },
		{ "Manhattan", manhattan },
		{ "Walking Distance", walkingDistance },
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	getHeuristic(int32_t h, const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		if (h < 0 || h >= heuristic::size)
			return (-1);
		return (heuristic::function[h].f(current, target));
	}
}
