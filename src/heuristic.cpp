/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/09/03 20:58:55 by othello          ###   ########.fr       */
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




#include "threadWorker.hpp"

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
					return (this->emptyPos < other.emptyPos);
				return (this->key < other.key);
			}
		};

		struct lookupTable
		{
			std::map<std::vector<int16_t>, int32_t>	h;
			std::set<queueNode>						visited;
			std::queue<queueNode>					queue;
			int32_t	(nPuzzle::Board::Tile::*getCoord)() const;

			int32_t	width;
			int32_t	height;
			bool	swapAxis;

			ThreadWorker	thread;
			std::vector<int16_t>	currentKey;
			std::vector<int16_t>	targetKey;

			lookupTable(int32_t (nPuzzle::Board::Tile::*getCoord)() const, bool swapAxis):
				getCoord(getCoord),
				width(-1),
				height(-1),
				swapAxis(swapAxis),
				thread([this]{ WalkingDistanceClass::expandLookupTable(*this); })
			{
			}

			void	resetLookupTable(const nPuzzle::Board& target)
			{
				std::lock_guard<std::mutex>	lock(this->thread.mutex);

				this->width = target.getWidth();
				this->height = target.getHeight();
				if (swapAxis)
					std::swap(this->width, this->height);
				this->h.clear();
				this->visited.clear();
				this->queue = {};
				queueNode	next;
				next.key = WalkingDistanceClass::generateKey(target, target, this->getCoord);
				next.emptyPos = (target.getEmptyTile().*this->getCoord)();
				next.depth = 0;
				this->queue.push(next);
			}
		};

		lookupTable	rowTable;
		lookupTable	colTable;
		
		int32_t					width;
		int32_t					height;

	public:
		WalkingDistanceClass(void):
			rowTable(&nPuzzle::Board::Tile::getY, false),
			colTable(&nPuzzle::Board::Tile::getX, true)
		{
			this->width = -1;
			this->height = -1;
		}
		~WalkingDistanceClass(void)
		{
		}

		int32_t	lookupHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target)
		{
#warning is only called once, returning -2. Needs to be called more often
			if (this->width != target.getWidth() || this->height != target.getHeight())
				this->resetLookupTables(target);

			int32_t	rowH = WalkingDistanceClass::lookupHeuristicHalf(current, target, this->rowTable);
			if (rowH < 0)
				return (rowH);

			int32_t	colH = WalkingDistanceClass::lookupHeuristicHalf(current, target, this->colTable);
			if (colH < 0)
				return (colH);

			return (rowH + colH);
		}

		void	resetLookupTables(const nPuzzle::Board& target)
		{
			this->width = target.getWidth();
			this->height = target.getHeight();
			this->rowTable.resetLookupTable(target);
			this->colTable.resetLookupTable(target);
		}

		static int32_t	lookupHeuristicHalf(const nPuzzle::Board& current, const nPuzzle::Board& target, lookupTable& table)
		{
			std::lock_guard<std::mutex>	lock(table.thread.mutex);

			std::vector<int16_t>	currentKey = WalkingDistanceClass::generateKey(current, target, table.getCoord);
			std::map<std::vector<int16_t>, int32_t>::iterator	found = table.h.find(currentKey);
			if (found != table.h.end())
				return (found->second);
			table.currentKey = currentKey;
			table.thread.setState(ThreadWorker::State::RUNNING);
			return (-2);
		}

		static std::vector<int16_t>	generateKey(const nPuzzle::Board& current, const nPuzzle::Board& target, int32_t (nPuzzle::Board::Tile::*getCoord)() const)
		{
			const int32_t	height = target.getHeight();
			const int32_t	size = target.getWidth() * height;
			std::vector<int16_t>	key(size, 0);

			for (int32_t value = 1; value < target.getSize(); ++value)
				++key[(current.getTile(value).*getCoord)() * height + (target.getTile(value).*getCoord)()];
			return (key);
		}

		static int32_t	expandLookupTable(lookupTable& table)
		{
			std::lock_guard<std::mutex>	lock(table.thread.mutex);

			if (table.queue.empty())
			{
				table.thread.setState(ThreadWorker::State::IDLE);
				return (-1);
			}
			// BFS
			queueNode	current = WalkingDistanceClass::extractTopFromQueue(table);
			if (!WalkingDistanceClass::updateVisitedList(table, current))
				return (-2);
			WalkingDistanceClass::addToLookupTable(table, current);
			WalkingDistanceClass::findAndCreateNewQueueNodes(table, current);
			// Making the BFS lazy
			if (current.key == table.currentKey)
			{
				if (table.thread.getState() != ThreadWorker::State::STOP)
					table.thread.setState(ThreadWorker::State::IDLE);
				return (current.depth);
			}
			return (-2);
		}

		static queueNode	extractTopFromQueue(lookupTable& table)
		{
			queueNode	top = std::move(table.queue.front());
			table.queue.pop();
			return (top);
		}

		static bool	updateVisitedList(lookupTable& table, const queueNode& current)
		{
			std::set<queueNode>::iterator	found = table.visited.find(current);
			if (found != table.visited.end())
			{
				if (found->depth <= current.depth)
					return (false);
				table.visited.erase(found);
			}
			table.visited.insert(current);
			return (true);
		}

		static void	addToLookupTable(lookupTable& table, const queueNode& current)
		{
			std::map<std::vector<int16_t>, int32_t>::iterator	found = table.h.find(current.key);

			if (found == table.h.end())
				table.h.emplace(current.key, current.depth);
			else
				found->second = current.depth;
		}

		static void	findAndCreateNewQueueNodes(lookupTable& table, const queueNode& current)
		{
			int32_t	emptyRow = current.emptyPos * table.width;
			for (int32_t targetLine : { current.emptyPos - 1, current.emptyPos + 1 })
			{
				if (targetLine < 0 || targetLine >= table.height)
					continue;
				int32_t	targetRow = targetLine * table.width;
				for (int32_t targetCol = 0; targetCol < table.width; ++targetCol)
				{
					int32_t	targetPos = targetRow + targetCol;
					if (current.key[targetPos] == 0)
						continue;
					queueNode	next;
					next.key = current.key;
					--next.key[targetPos];
					++next.key[emptyRow + targetCol];
					next.emptyPos = targetLine;
					next.depth = current.depth + 1;
					table.queue.push(next);
				}
			}
		}
};

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
		{ "Linear Conflicts", LinearConflicts},
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
