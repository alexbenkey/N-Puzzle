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
#include <set>		// std::set

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
			struct queueNode
			{
				std::vector<int16_t>	key;
				int32_t					emptyPos;
				int32_t					depth;

				bool	operator<(const queueNode& other) const
				{
					if (this->emptyPos != other.emptyPos)
						return this->emptyPos < other.emptyPos;
					return this->key < other.key;
				}
			};

#warning	"Does not take width vs height into account"
			struct lookupTable
			{
				std::queue<queueNode>					queue;
				std::set<queueNode>						visited;
				std::map<std::vector<int16_t>, int32_t>	h;
				const int32_t	(nPuzzle::Board::Tile::*getCoord)() const;
			};

			int32_t		width;
			int32_t		height;
			int32_t		size;
			lookupTable	row;
			lookupTable	col;

			void	resetLookupTable(const nPuzzle::Board& target);
			int32_t	lookupHeuristicHalf(const nPuzzle::Board& current, const nPuzzle::Board& target, lookupTable& table);
			std::vector<int16_t>	generateKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const) const;
			int32_t	expandLookupTable(lookupTable& table, const std::vector<int16_t>& key);

		public:
			WalkingDistanceClass(void);

			int32_t	lookupHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target);
			void	printQueue(std::queue<queueNode>& queue);
			void	printQueueNode(const queueNode& node) const;
			void	printKey(const std::vector<int16_t>& key, char delim = ' ') const;
			void	printLookupTable(const lookupTable& table) const;
	};

	WalkingDistanceClass::WalkingDistanceClass(void)
	{
		this->width = -1;
		this->height = -1;
		this->size = -1;
		this->row.getCoord = &nPuzzle::Board::Tile::getY;
		this->col.getCoord = &nPuzzle::Board::Tile::getX;
	}

	int32_t	WalkingDistanceClass::lookupHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		if (this->width != target.getWidth() || this->height != target.getHeight())
			resetLookupTable(target);

		int32_t	rowH = this->lookupHeuristicHalf(current, target, this->row);
		if (rowH < 0)
			return (-1);
		
		int32_t	colH = this->lookupHeuristicHalf(current, target, this->col);
		if (colH < 0)
			return (-1);

		return (rowH + colH);
	}

	int32_t	WalkingDistanceClass::lookupHeuristicHalf(const nPuzzle::Board& current, const nPuzzle::Board& target, lookupTable& table)
	{
		std::vector<int16_t>	currentKey = this->generateKey(current, target, table.getCoord);
		std::map<std::vector<int16_t>, int32_t>::iterator found = table.h.find(currentKey);
		if (found != table.h.end())
			return (found->second);
		return (this->expandLookupTable(table, currentKey));
	}

	void	WalkingDistanceClass::resetLookupTable(const nPuzzle::Board& target)
	{
		this->width = target.getWidth();
		this->height = target.getHeight();
		this->size = this->width * this->height;

		{
			this->row.h.clear();
			this->row.visited.clear();
			this->row.queue = {};
			queueNode	newNode;
			newNode.key = generateKey(target, target, this->row.getCoord);
			newNode.emptyPos = (target.getEmptyTile().*this->row.getCoord)();
			newNode.depth = 0;
			this->row.queue.push(newNode);
		}
		{
			this->col.h.clear();
			this->col.visited.clear();
			this->col.queue = {};
			queueNode	newNode;
			newNode.key = generateKey(target, target, this->col.getCoord);
			newNode.emptyPos = (target.getEmptyTile().*this->col.getCoord)();
			newNode.depth = 0;
			this->col.queue.push(newNode);
		}
	}

	std::vector<int16_t>	WalkingDistanceClass::generateKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const) const
	{
		std::vector<int16_t>	key(this->width * this->height, 0);

		for (int32_t value = 0; value < this->size; ++value)
			++key[(current.getTile(value).*getCoord)() * this->height + (target.getTile(value).*getCoord)()];
		return (key);
	}

	int32_t	WalkingDistanceClass::expandLookupTable(lookupTable& table, const std::vector<int16_t>& key)
	{
		while (!table.queue.empty())
		{
			// Extract top node from queue
			queueNode	current = table.queue.front();
			table.queue.pop();
			// Update visited
			std::set<queueNode>::iterator found = table.visited.find(current);
			if (found != table.visited.end())
			{
				if (found->depth <= current.depth)
					continue;
				table.visited.erase(found);
			}
			table.visited.insert(current);
			// Add to lookup table
			auto foundh = table.h.find(current.key);
			if (foundh == table.h.end())
				table.h.emplace(current.key, current.depth);
			else if (foundh->second > current.depth)
				foundh->second = current.depth;
			// Find and create new queue nodes
#warning	"Doesn't seem to create proper h depths"
			int32_t	emptyRow = current.emptyPos * this->width;
			for (int32_t emptyCol = 0; emptyCol < this->width; ++emptyCol)
			{
				if (current.key[emptyRow + emptyCol] == 0)
					continue;
				for (int32_t tRow : { current.emptyPos - 1, current.emptyPos + 1} )
				{
					if (tRow < 0 || tRow >= this->height)
						continue;
					int32_t	targetRow = tRow * this->width;
					for (int32_t targetCol = 0; targetCol < this->width; ++targetCol)
					{
						if (targetCol == emptyCol || current.key[targetRow + targetCol] == 0)
							continue;
						queueNode	next;
						next.key = current.key;
						--next.key[emptyRow + emptyCol];
						++next.key[targetRow + emptyCol];
						--next.key[targetRow + targetCol];
						++next.key[emptyRow + targetCol];
						next.emptyPos = tRow;
						next.depth = current.depth + 1;
						if (table.visited.find(next) != table.visited.end())
							continue;
						table.queue.push(next);
					}
				}
			}
			// Check for key for lazy BFS
			if (current.key == key)
				return (current.depth);
		}
		return (-1);
	}

	void	WalkingDistanceClass::printQueue(std::queue<queueNode>& queue)
	{
		for (size_t i = 0; i < queue.size(); ++i)
		{
			queueNode	node = queue.front();
			queue.pop();
			queue.push(node);
			std::cerr	<< "queue "	<< i;
			printQueueNode(node);
		}
	}

	void	WalkingDistanceClass::printQueueNode(const queueNode& node) const
	{
		std::cerr	<< "[ ";
		this->printKey(node.key);
		std::fprintf(stderr, "]\td:%4i  e:%4i\n", node.depth, node.emptyPos);
		std::cerr	<< std::flush;
	}


	void	WalkingDistanceClass::printKey(const std::vector<int16_t>& key, char delim) const
	{
		for (size_t i = 0; i < key.size(); ++i)
		{
			std::cerr	<< key[i];
			if ((int32_t)i % this->width == this->width - 1)
				std::cerr	<< delim;
			else
				std::cerr	<< ' ';
		}
		std::cerr	<< std::flush;
	}

	void	WalkingDistanceClass::printLookupTable(const lookupTable& table) const
	{
		for (auto i : table.h)
		{
			this->printKey(i.first);
			std::cerr	<< "\th: "	<< i.second	<< '\n';
		}
		std::cerr	<< std::flush;
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
