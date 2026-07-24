/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/24 16:53:33 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "nPuzzle.State.hpp"
#include "nPuzzle.Target.hpp"

#include "colors.hpp"
#include "heuristic.hpp"

#include <iostream>	// std::stream
#include <algorithm>	// std::sort

/** ************************************************************************ **\
 * 
 * 	Constructors
 * 
\* ************************************************************************** */

nPuzzle::nPuzzle(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setVariables(0, 0);
}

nPuzzle::nPuzzle(std::istream& __is)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Parsing constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setVariables(0, 0);
	this->parse(__is);
}


nPuzzle::nPuzzle(const int32_t widthAndHeight)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setVariables(widthAndHeight, widthAndHeight);
}

nPuzzle::nPuzzle(const int32_t width, const int32_t height)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Default constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	this->setVariables(width, height);
}

nPuzzle::nPuzzle(const nPuzzle &src)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DGREEN	<< "Copy constructor "
				<< C_GREEN	<< __func__
				<< C_DGREEN	<< " called."
				<< C_RESET	<< std::endl;
#endif
	*this = src;
}

void	nPuzzle::setVariables(const int32_t width, const int32_t height)
{
	this->width = (height == 0) ? width : 0;
	this->height = (width == 0) ? height : 0;
	this->size = this->width * this->height;
	this->start = nullptr;
	this->state = nullptr;
	this->target = nullptr;
}

/** ************************************************************************ **\
 * 
 * 	Deconstructors
 * 
\* ************************************************************************** */

nPuzzle::~nPuzzle(void)
{
#if DEBUG >= DEBUG_TRACE
	std::cout	<< C_DRED	<< "Deconstructor "
				<< C_RED	<< __func__
				<< C_DRED	<< " called"
				<< C_RESET	<< std::endl;
#endif
	this->clearAll();
}

void	nPuzzle::clearAll(void)
{
	this->clearProgress();
	this->clearBoard();
}

void	nPuzzle::clearProgress(void)
{
	this->clearQueue();
	this->clearVisited();
}

void	nPuzzle::clearBoard(void)
{
	this->clearState(&this->state);
	this->clearState(&this->start);
	this->clearTarget();
}

void	nPuzzle::clearQueue(void)
{
	for (nPuzzle::State *state : this->queue)
		delete state;
	this->queue.clear();
	this->queueIndex = -1;
}

void	nPuzzle::clearVisited(void)
{
	for (nPuzzle::State *state : this->visited)
		delete state;
	this->visited.clear();
}

void	nPuzzle::clearState(nPuzzle::State** state)
{
	if (*state != nullptr)
	{
		delete *state;
		*state = nullptr;
	}
}

void	nPuzzle::clearTarget(void)
{
	if (this->target != nullptr)
	{
		delete this->target;
		this->target = nullptr;
	}
}


/** ************************************************************************ **\
 * 
 * 	Member Functions
 * 
\* ************************************************************************** */

void	nPuzzle::parse(std::istream& __is)
{
	std::string	line;
	std::vector<int32_t>	numbers;

	// Clearing current Content
#warning clearing before parsing needs to be implemented

	// Reading upto puzzle size
	while (std::getline(__is, line))
	{
		if (emptyLine(line))
			continue;
		if (!validLine(line))
			throw std::runtime_error("Invalid puzzle size line: " + line);
		break;
	}
	numbers = nPuzzle::convertLineToNumbers(line);
	size_t	size = numbers.size();
	if (size < 1 || size > 2)
		throw std::runtime_error("Invalid puzzle size line: expected 1 or 2 positive integers");
	if (numbers[0] <= 0)
		throw std::runtime_error("Invalid puzzle size line: expected 1 or 2 positive integers");
	this->width = numbers[0];
	if (numbers[size - 1] <= 0)
		throw std::runtime_error("Invalid puzzle size line: expected 1 or 2 positive integers");
	this->height = numbers[size - 1];
	this->size = this->width * this->height;
	this->state = new nPuzzle::State(this->width, this->height);
	this->target = new nPuzzle::Target();
	this->target->setSize(this->width, this->height);

	// Reading puzzle tiles
	for (int32_t row = 0; std::getline(__is, line); ++row)
	{

		if (!validLine(line) || emptyLine(line))
			throw std::runtime_error("Invalid puzzle row line: " + line);
		numbers = nPuzzle::convertLineToNumbers(line);
		this->setRow(row, numbers);
	}
	this->calculateHeuristic();
	this->storeStartState();
}

bool	nPuzzle::emptyLine(const std::string &line) const
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size && std::isspace(static_cast<unsigned char>(line[i])))
		++i;
	return (i == size || line[i] == '#');
}

bool	nPuzzle::validLine(const std::string &line) const
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size
		&& (std::isspace(static_cast<unsigned char>(line[i]))
			|| std::isdigit(static_cast<unsigned char>(line[i]))))
		++i;
	return (i == size || line[i] == '#');
}

std::vector<int32_t>	nPuzzle::convertLineToNumbers(const std::string& line)
{
	std::istringstream	iss(line);
	int32_t					x;
	std::vector<int32_t>	numbers;

	while (iss >> x)
		numbers.push_back(x);
	return (numbers);
}

void	nPuzzle::setRow(int32_t row, const std::vector<int>& numbers)
{
	if (row < 0 || row >= this->height)
		throw std::runtime_error(std::string("Invalid puzzle row: "));
	if (numbers.size() != static_cast<size_t>(this->width))
		throw std::runtime_error(std::string("Invalid number of tiles in row "));

	for (int32_t x = 0; x < this->width; ++x)
	{
		this->state->addTile(numbers[x], x, row);
		// nPuzzle::Board::Tile tile = this->state->getTile(x, row);
		// tile.setVal(numbers[x]);
		// this->state->getTile(x, row).setVal(numbers[x]);
		// if (numbers[x] == 0)
		// 	this->state->setEmptyPos(x, row);
		// this->state->getTile(x, row).setxPos(x);
		// this->state->getTile(x, row).setyPos(row);
	}
}

nPuzzle::State&	nPuzzle::getQueueState(void)
{
	if (this->queueIndex == -1)
		return (*this->state);
	else
		return (*this->queue.at(this->queueIndex));
}

void	nPuzzle::maintainValidQueue(void)
{
	size_t	size = this->queue.size();

	if (size == 0)
		this->queueIndex = -1;
	else if (this->queueIndex < 0)
		this->queueIndex = 0;
	else if (this->queueIndex >= (int32_t)size)
		this->queueIndex = size - 1;

#if DEBUG >= DEBUG_DEBUG
	std::cerr	<< __func__	<< '['	<< __LINE__	<< ']'
				<< "queueIndex: "	<< this->queueIndex
				<< std::endl;
#endif
}

void	nPuzzle::storeStartState(void)
{
	if (this->state == nullptr)
		throw std::runtime_error("Failed to set Start state. No State present");
	this->clearState(&this->start);
	this->start = new nPuzzle::State(*this->state);
}

bool	nPuzzle::move(nPuzzle::Direction direction, int32_t h)
{
	bool	validMove;

	validMove = this->state->move(direction);
	if (validMove)
	{
		this->clearProgress();
		if (h != -1)
			this->calculateHeuristic(h);
		else
			this->calculateHeuristic();
	}
	return (validMove);
}


bool	nPuzzle::moveUp(int32_t h)
{
	return(this->move(nPuzzle::Direction::UP, h));
}

bool	nPuzzle::moveDown(int32_t h)
{
	return(this->move(nPuzzle::Direction::DOWN, h));
}

bool	nPuzzle::moveLeft(int32_t h)
{
	return(this->move(nPuzzle::Direction::LEFT, h));
}

bool	nPuzzle::moveRight(int32_t h)
{
	return(this->move(nPuzzle::Direction::RIGHT, h));
}



void	nPuzzle::solve(int32_t h)
{
	if (h >= heuristic::size)
		return ;
#warning needs to validate puzzle solved state
	// while puzzle is unsolved
	while (true)
		this->solveStep(h);
}

void	nPuzzle::solveStep(int32_t h)
{
#if DEBUG >= DEBUG_DEBUG
	std::printf("%s[%i]\n", __func__, __LINE__);
#endif

#warning needs to validate puzzle solved state
	// if puzzle is solved
	if (false)
		return ;

	if (this->queue.size() == 0)
		this->processState(new nPuzzle::State(*this->state), h);

	nPuzzle::State*	current = this->queue.front();
	this->queue.erase(this->queue.begin());
	// if (current->sameState(*this->target))
	// 	return ;
	this->visited.push_back(current);
	for (nPuzzle::Direction direction : {
			nPuzzle::Direction::UP,
			nPuzzle::Direction::RIGHT,
			nPuzzle::Direction::DOWN,
			nPuzzle::Direction::LEFT
		}) {
			nPuzzle::State*	next = new nPuzzle::State(*current);
			if (next->move(direction))
				this->processState(next, h);
			else
				delete next;
		}

	this->maintainValidQueue();
#if DEBUG >= DEBUG_DEBUG
	std::printf("%s[%i] queue.size = %lu\n", __func__, __LINE__, this->queue.size());
#endif
}

void	nPuzzle::processState(nPuzzle::State* state, int32_t h)
{
	if (!state->setUsedHeuristic(h))
	{
		delete state;
		return;
	}
	if (this->stateHasAlreadyBeenVisited(state))
		return ;
	if (this->stateIsAlreadyInQueue(state))
		return ;
	if (h != -1)
		state->calculateHeuristic(h, this->target->getBoard());
	else
		state->calculateHeuristic(this->target->getBoard());
	this->queue.push_back(state);
	std::sort(
		this->queue.begin(), 
		this->queue.end(), 
		[](const nPuzzle::State* lhs, const nPuzzle::State *rhs)
		{
			return *lhs < *rhs;
		});
	std::cout << "Sorted queue:\n";
	for (const nPuzzle::State* state : this->queue)
	{
		const int32_t h = state->getUsedHeuristic(); // Manhattan
		std::cout
		<< "used= " << h
		<< "g=" << state->getCost()
		<< ", h=" << state->getHeuristic(h)
		<< ", f=" << state->getCost() + state->getHeuristic(h)
		<< '\n';
	}
};

bool	nPuzzle::stateHasAlreadyBeenVisited(nPuzzle::State* state)
{
	std::vector<nPuzzle::State*>::iterator	foundItem;

	foundItem = std::find_if(
		this->visited.begin(), 
		this->visited.end(), 
		[state] (const nPuzzle::State* candidate){return candidate->sameState(*state);});
	if (foundItem == this->visited.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->visited.erase(foundItem);
		return (false);
	}
	return (true);
}

bool	nPuzzle::stateIsAlreadyInQueue(nPuzzle::State* state)
{
	std::vector<nPuzzle::State*>::iterator	foundItem;

	foundItem = std::find_if(this->queue.begin(), this->queue.end(), [state] (const nPuzzle::State *candidate){ return candidate->sameState(*state); });
	if (foundItem == this->queue.end())
		return (false);
	if (state->getCost() < (*foundItem)->getCost())
	{
		this->queue.erase(foundItem);
		return (false);
	}
	return (true);
}

void	nPuzzle::calculateHeuristic(void)
{
	for (int32_t h = 0; h < heuristic::size; ++h)
		this->state->calculateHeuristic(h, this->target->getBoard());
}

void	nPuzzle::calculateHeuristic(int32_t h)
{
	this->state->calculateHeuristic(h, this->target->getBoard());
}


void	nPuzzle::printPuzzle(void)
{
	std::cerr	<< *this->state	<< std::flush;
}

void	nPuzzle::printTarget(void)
{
	std::cerr	<< "# Target\n"
				<< *this->target	<< std::flush;
}

void	nPuzzle::printQueue(void)
{
	if (this->queue.size())
		std::cerr	<< "# Queue["	<< this->queueIndex	<< "]\n"
					<< *this->queue[this->queueIndex]	<< std::flush;
}

// void	nPuzzle::printEmptyTilePos(void)
// {
// 	this->state->printTilePos( this->state->getTile(0));
// }


// void	nPuzzle::printAllTiles(const nPuzzle::State& state) const
// {
// 	for (int32_t x = 0, width = state.getPuzzleWidth(); x < width; ++x)
// 	{
// 		for (int32_t y = 0, height = state.getPuzzleHeight(); y < height; ++y)
// 		{
// 			nPuzzle::Board::Tile tile = state.getTile(x, y);
// 			std::printf("%2i [%2i][%2i] ", tile.getVal(), tile.getxPos(), tile.getyPos());
// 			state.printTilePos(tile);
// 		}
// 	}
// 	std::cout	<< std::endl;
// }

// void	nPuzzle::printAllTilesFlex(nPuzzle::State& state)
// {
// 	for (int32_t value = 1, size = state.getPuzzleSize(); value < size; ++value)
// 	{
// 		nPuzzle::Board::Tile tile = state.getTile(value);
// 		std::printf("%2i [%2i][%2i] ", tile.getVal(), tile.getxPos(), tile.getyPos());
// 		state.printTilePos(tile);
// 	}
// 	std::cout	<< std::endl;
// }

void	nPuzzle::resetToStart(void)
{
	this->clearQueue();
	this->clearVisited();
	this->clearState(&this->state);
	// this->start = new nPuzzle::State(this->start);
}

// void	nPuzzle::resetStates(void)
// {
// 	this->clearStates();
// 	this->state = this->start; 
// }

// void	nPuzzle::clearStates(void)
// {
// 	for (nPuzzle::State *state : this->queue)
// 		delete state;
// 	this->queue.clear();
// 	for (nPuzzle::State *state : this->visited)
// 		delete state;
// 	this->visited.clear();

// 	this->queueIndex = -1;
// }

/** ************************************************************************ **\
 * 
 * 	Operators
 * 
\* ************************************************************************** */

nPuzzle	&nPuzzle::operator=(const nPuzzle &src)
{
	if (this == &src)
		return (*this);
	// set width height and size
	this->setVariables(src.width, src.height);
	// set state
	if (src.state)
		this->state = new nPuzzle::State(*src.state);
	// set start
	if (src.start != nullptr)
		this->start = new nPuzzle::State(*src.start);
	else if (this->state != nullptr)
		this->start = new nPuzzle::State(*src.state);
	// set target
	if (src.target != nullptr)
		this->target = new nPuzzle::Target(*src.target);
	else if (this->size != 0)
		this->target = new nPuzzle::Target(this->width, this->height);
	return (*this);
}
