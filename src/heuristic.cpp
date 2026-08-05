/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 12:51:34 by othello           #+#    #+#             */
/*   Updated: 2026/08/04 18:29:35 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>	// std::abs()

#include "heuristic.hpp"
#include "nPuzzle.Board.hpp"
#include "nPuzzle.Board.Tile.hpp"

#include <iostream>

	# include <queue>
	# include <unordered_set>
	# include <map>
	# include <set>

namespace
{
	int32_t	manhattan(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		int32_t	heuristic = 0;
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);

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

	// bool	matchRows(const nPuzzle::Board& current, const nPuzzle::Board& target)
	// {
	// 	for (int32_t i = 1; i < target.getSize(); ++i)
	// 		if (current.getTile(i).getY() != target.getTile(i).getY())
	// 			return (false);
	// 	return (true);
	// }

	// bool	matchColumns(const nPuzzle::Board& current, const nPuzzle::Board& target)
	// {
	// 	for (int32_t i = 1; i < target.getSize(); ++i)
	// 		if (current.getTile(i).getX() != target.getTile(i).getX())
	// 			return (false);
	// 	return (true);
	// }

	// int32_t	walkerDistanceBFS(nPuzzle::Board board, const nPuzzle::Board& target, bool (*match)(const nPuzzle::Board&, const nPuzzle::Board&))
	// {
	// 	std::queue<std::pair<int32_t, nPuzzle::Board> >	queue;
	// 	std::unordered_set<nPuzzle::Board, BoardHash>	visited;

	// 	if (match(board, target))
	// 		return (0);
	// 	queue.push({0, board});
	// 	visited.insert(board);
	// 	while (!queue.empty())
	// 	{
	// 		auto	current = queue.front();
	// 		queue.pop();
	// 		for (nPuzzle::Direction direction :
	// 		{
	// 			nPuzzle::Direction::UP,
	// 			nPuzzle::Direction::RIGHT,
	// 			nPuzzle::Direction::DOWN,
	// 			nPuzzle::Direction::LEFT,
	// 		})
	// 		{
	// 			nPuzzle::Board	next = current.second;
	// 			if (next.move(direction))
	// 			{
	// 				if (visited.find(next) != visited.end())
	// 					continue;
	// 				if (match(next, target))
	// 					return (current.first + 1);
	// 				queue.push({current.first + 1, next});
	// 				visited.insert(next);
	// 			}
	// 		}
	// 	}
	// 	return (-1);
	// }

	std::vector<int16_t>	createKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const)
	{
		int32_t	size = current.getSize();
		int32_t width = current.getWidth();
		std::vector<int16_t>	key(size, 0);

		for (int i = 0; i < size; ++i)
		{
			key[current.getTile(i).getY() * width + current.getTile(i).getX()] = (target.getTile(i).*getCoord)();
		}
		return (key);
	}

	// std::vector<int16_t>	createRowKey(const nPuzzle::Board& board, const nPuzzle::Board& target)
	// {
	// 	int32_t	size = board.getSize();
	// 	int32_t width = board.getWidth();
	// 	std::vector<int16_t>	key(size, 0);

	// 	for (int i = 0; i < size; ++i)
	// 	{
	// 		key[board.getTile(i).getY() * width + board.getTile(i).getX()] = target.getTile(i).getY();
	// 	}
	// 	return (key);
	// }

	// void	WalkerDistanceLoopupTable(const nPuzzle::Board& target, const nPuzzle::Board& current)
	// {
	// 	static bool	initialized = false;
	// 	static nPuzzle::Board cmp;

	// 	if (initialized == true && target == cmp)
	// 		return ;
	// 	cmp = target;
	// 	std::cout	<< "Generate new lookup table\n"
	// 				// << " row: "	<< walkerDistanceBFS(current, target, matchRows)	<< '\n'
	// 				// << " col: "	<< walkerDistanceBFS(current, target, matchColumns)	<< '\n'
	// 				<< std::flush;
	// 	for (auto i : createKey(current, target, &nPuzzle::Board::Tile::getY))
	// 		std::cout	<< i	<< '\n';
	// 	for (auto i : createKey(current, target, &nPuzzle::Board::Tile::getX))
	// 		std::cout	<< i	<< '\n';
	// 	std::cout	<< std::flush;
	// 	initialized = true;
	// 	return ;
	// }

	class WalkerDistanceClass
	{
		private:
			struct queueNode
			{
				std::vector<int16_t>	key;
				int32_t					emptyPos;
				std::size_t				depth;
				bool operator<(const queueNode& rhs) const
				{
					return std::tie(this->key, this->emptyPos) < std::tie(rhs.key, rhs.emptyPos);
				}
			};
			struct lookupTable
			{
				std::map<std::vector<int16_t>, int32_t>	h;
				std::queue<queueNode>					queue;
				std::set<queueNode>						visited;
				const int32_t 							(nPuzzle::Board::Tile::*getCoord)() const;
			};
			lookupTable	row;
			lookupTable column;
			int32_t	width;
			int32_t	height;

			int32_t	getHeuristicHalf(lookupTable& table, const nPuzzle::Board& current, const nPuzzle::Board& target);
			std::vector<int16_t>	convertBoardToKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const) const;
			void	resetLookupTable(const nPuzzle::Board& target);

		public:
			WalkerDistanceClass(void);

			int32_t	getHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target);
			void	printLookupTable(void) const;
	};

	WalkerDistanceClass::WalkerDistanceClass(void)
	{
		this->row.getCoord = &nPuzzle::Board::Tile::getY;
		this->column.getCoord = &nPuzzle::Board::Tile::getX;
		this->width = -1;
		this->height = -1;
	}

	void	WalkerDistanceClass::resetLookupTable(const nPuzzle::Board& target)
	{
		std::setvbuf(stderr, nullptr, _IONBF, 0);
std::fprintf(stderr, "%s::%s[%i] \n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		this->width = target.getWidth();
		this->height = target.getHeight();
		const nPuzzle::Board::Tile& emptyTile = target.getEmptyTile();
		int32_t	emptyPos = emptyTile.getY() * this->width + emptyTile.getX();
		{
			this->row.h.clear();
			this->row.queue = {};
			this->row.visited.clear();
			queueNode	node;
			node.key = this->convertBoardToKey(target, target, row.getCoord);
			node.emptyPos = emptyPos;
			node.depth = 0;
			this->row.queue.push(node);
		}
		{
			this->column.h.clear();
			this->column.queue = {};
			this->column.visited.clear();
			queueNode	node;
			node.key = this->convertBoardToKey(target, target, column.getCoord);
			node.emptyPos = emptyPos;
			node.depth = 0;
			this->column.queue.push(node);
		}
	}

	int32_t	WalkerDistanceClass::getHeuristic(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		// Validate target size
		if (this->width != target.getWidth() || this->height != target.getHeight())
			this->resetLookupTable(target);
		// Get Heuristics from lookuptable
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		int32_t	rowH = this->getHeuristicHalf(this->row, current, target);
		// if (rowH < 0)
			// return (-1);
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		int32_t	colH = this->getHeuristicHalf(this->column, current, target);
		if (colH < 0)
			return (-1);
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		return (rowH + colH);
	}

	// int32_t	WalkerDistanceClass::getHeuristicHalf(lookupTable& table, const nPuzzle::Board& current, const nPuzzle::Board& target)
	// {
	// 	// Create Key for current
	// 	std::vector<int16_t>	currentKey = this->convertBoardToKey(current, target, table.getCoord);
	// 	// Find key in existing lookup Table
	// 	if (table.h.find(currentKey) != table.h.end())
	// 		return (table.h[currentKey]);
	// 	while (!table.queue.empty())
	// 	{
	// 		// Retrieve top item
	// 		queueNode	top = table.queue.front();
	// 		table.queue.pop();
	// 		// Check and add visited state
	// 		if (!table.visited.insert(top).second)
	// 			continue;
	// 		// Add depth to map if key does not exist yet
	// 		if (table.h.find(top.key) == table.h.end())
	// 			table.h.emplace(top.key, top.depth);
	// 		else if (table.h.find(top.key)->second > top.depth)
	// 			table.h.find(top.key)->second = top.depth;
	// 		// Create new queue items
	// 		for (int32_t dir : { -1, -this->width, 1, this->width })
	// 		{
	// 			int32_t newPos = top.emptyPos + dir;
	// 			if (newPos >= 0 && newPos < top.key.size() &&
	// 				(newPos / this->width == top.emptyPos / this->width || 
	// 				newPos % this->width == top.emptyPos % this->width))
	// 			{
	// 				queueNode	next = top;
	// 				std::swap(next.key.at(top.emptyPos), next.key.at(top.emptyPos + dir));
	// 				next.emptyPos += dir;
	// 				++next.depth;
	// 				table.queue.push(next);
	// 			}
	// 		}
	// 		if (top.key == currentKey)
	// 		{
	// 			return (top.depth);
	// 		}
	// 	}
	// 	return (-1);
	// }

	int32_t	WalkerDistanceClass::getHeuristicHalf(lookupTable& table, const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		// Create Key for current
		std::vector<int16_t>	currentKey = this->convertBoardToKey(current, target, table.getCoord);
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		// Find key in existing lookup Table
		if (table.h.find(currentKey) != table.h.end())
			return (table.h[currentKey]);
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		while (!table.queue.empty())
		{
			// Retrieve top item
			queueNode	top = table.queue.front();
			table.queue.pop();
			// Check and add visited state
			if (!table.visited.insert(top).second)
				continue;
			// Add depth to map if key does not exist yet
			if (table.h.find(top.key) == table.h.end())
				table.h.emplace(top.key, top.depth);
			else if (table.h.find(top.key)->second > top.depth)
				table.h.find(top.key)->second = top.depth;
			// Create new queue items
			for (int8_t dir : {-1, 1})
			{
				int32_t currentRow = top.emptyPos;
				int32_t targetRow = top.emptyPos + dir;
				if (targetRow < 0 || targetRow >= this->height)
					continue;
				for (int32_t i = 0; i < this->width; ++i)
				{
					if (top.key[currentRow * this->width + i])
						for (int32_t j = 0; j < this->width; ++j)
						{
							if (i != j)
							{
								queueNode	next = top;
								++next.key[currentRow * this->width + i];
								--next.key[targetRow * this->width + j];
								next.emptyPos = targetRow;
								++next.depth;
								table.queue.push(next);
							}
						}
				}
			}
			if (top.key == currentKey)
			{
				return (top.depth);
			}
		}
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		return (-1);
	}

	// std::vector<int16_t>	WalkerDistanceClass::convertBoardToKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const) const
	// {
	// 	int32_t	size = current.getSize();
	// 	int32_t width = current.getWidth();
	// 	std::vector<int16_t>	key(size, 0);

	// 	for (int i = 0; i < size; ++i)
	// 	{
	// 		key[current.getTile(i).getY() * width + current.getTile(i).getX()] = (target.getTile(i).*getCoord)();
	// 	}
	// 	return (key);
	// }
	std::vector<int16_t>	WalkerDistanceClass::convertBoardToKey(const nPuzzle::Board& current, const nPuzzle::Board& target, const int32_t (nPuzzle::Board::Tile::*getCoord)() const) const
	{
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		std::vector<int16_t>	key(this->width * this->height, 0);

		for (int value = 0; value < this->width * this->height; ++value)
		{
std::fprintf(stderr, "%s:%s[%i] value: %i\n", __FILE__, __func__, __LINE__, value); std::fflush(stderr);
			int32_t	coord = (current.getTile(value).*getCoord)();
std::fprintf(stderr, "%s:%s[%i] coord: %i\n", __FILE__, __func__, __LINE__, coord); std::fflush(stderr);
			int32_t	goal = (target.getTile(value).*getCoord)();
std::fprintf(stderr, "%s:%s[%i] goal: %i\n", __FILE__, __func__, __LINE__, goal); std::fflush(stderr);
std::fprintf(stderr,
    "width=%d height=%d size=%zu index=%d\n",
    this->width,
    this->height,
    key.size(),
    coord * this->height + goal); std::fflush(stderr);
			// key.at(coord * this->height + goal)++;
			++key[coord * this->height + goal];
std::cerr	<< std::flush;
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		}
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		return (key);
	}

	void	WalkerDistanceClass::printLookupTable(void) const
	{
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		std::cerr	<< "Row lookup table\n";
		for (auto entry : this->row.h)
		{
			std::cerr	<< entry.second	<< '\n';
			int32_t i = 0;
			for (auto keypart : entry.first)
			{
				std::cerr	<< keypart	<< ' ';
				// if (i++ % this->width == this->width - 1)
					// std::cerr	<< '\n';
			}
			std::cerr	<< '\n';
		}
		std::cerr	<< "Column lookup table\n";
		for (auto entry : this->column.h)
		{
			std::cerr	<< entry.second	<< '\n';
			int32_t i = 0;
			for (auto keypart : entry.first)
			{
				std::cerr	<< keypart	<< ' ';
				// if (i++ % this->width == this->width - 1)
					// std::cerr	<< '\n';
			}

			std::cerr	<< '\n';
		}
		std::cerr	<< std::flush;
	}

	void	printKey(std::vector<int16_t>& key, int32_t width)
	{
		int32_t	i = 0;
		for (auto val: key)
		{
			std::cerr	<< val;
			if (i % width == width - 1)
				std::cerr	<< std::endl;
			else
				std::cerr	<< ' ';
			++i;
		}
	}

	int32_t walkerDistance(const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
std::fprintf(stderr, "%s:%s[%i]\n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		static WalkerDistanceClass	walkerDistance;
		// return (-1);

std::fprintf(stderr, "%s::%s[%i] \n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		int32_t	h = walkerDistance.getHeuristic(current, target);
		// walkerDistance.printLookupTable();
std::fprintf(stderr, "%s::%s[%i] \n", __FILE__, __func__, __LINE__); std::fflush(stderr);
		return (walkerDistance.getHeuristic(current, target));
		// static std::map<std::vector<int16_t>, int32_t>	rowH;
		// static std::queue<WalkerQueue>					rowQueue;
		// static std::map<std::vector<int16_t>, int32_t>	colH;

		// std::vector<int16_t>	rowKey = createKey(current, target, &nPuzzle::Board::Tile::getY);
		// if (rowH.find(rowKey) == rowH.end())
		// 	expandLookUpTable(rowH, rowQueue, rowKey, target);
		// if (rowH.find(rowKey) == rowH.end())
		// 	throw std::runtime_error("Could not find row Heuristic");
		
		// std::vector<int16_t>	colKey = createKey(current, target, &nPuzzle::Board::Tile::getX);
		// if (colH.find(colKey) == colH.end())
		// 	std::cout	<< "calculate colHeuristics"	<< std::endl;

		// return (rowH[rowKey] + colH[colKey]);



		// int32_t	heuristic = 0;

		// // heuristic = walkerDistanceBFS(current, target, matchRows) + walkerDistanceBFS(current, target, matchColumns);
		
		// WalkerDistanceLoopupTable(target, current);
		// return (heuristic);
	}
}

namespace heuristic
{
	const List	function[] =
	{
		{ "Displaced", displaced },
		{ "Manhattan", manhattan },
		{ "Walker Distance", walkerDistance },
	};

	const int32_t	size = sizeof(function) / sizeof(List);

	int32_t	getHeuristic(int32_t h, const nPuzzle::Board& current, const nPuzzle::Board& target)
	{
		if (h < 0 || h >= heuristic::size)
			return (-1);
		return (heuristic::function[h].f(current, target));
	}
}
