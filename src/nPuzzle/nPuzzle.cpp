/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:13:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/30 17:21:47 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "nPuzzle.State.hpp"
#include "nPuzzle.Target.hpp"
#include "nPuzzle.Solver.hpp"

#include "colors.hpp"
#include "heuristic.hpp"
#include "Errors.hpp"

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
	this->solver = new nPuzzle::Solver(*this);
}

void	nPuzzle::setVariables(const int32_t width, const int32_t height)
{
	this->width = (height == 0) ? width : 0;
	this->height = (width == 0) ? height : 0;
	this->size = this->width * this->height;
	this->start = nullptr;
	this->state = nullptr;
	this->target = nullptr;
	this->solver = new nPuzzle::Solver(*this);
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
	delete this->solver;
}

void	nPuzzle::clearAll(void)
{
	this->clearSolver();
	this->clearBoard();
}

void	nPuzzle::clearSolver(void)
{
	this->solver->clearQueue();
}

void	nPuzzle::clearBoard(void)
{
	this->clearState(&this->state);
	this->clearState(&this->start);
	this->clearTarget();
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
		this->state->addTile(numbers[x], x, row);
}

const nPuzzle::State&	nPuzzle::getQueueState(void)
{
	return (this->solver->getTopState());
}

void	nPuzzle::incrementHeuristic(void)
{
	++this->heuristicIndex;
	this->maintainValidHeuristic();
}

void	nPuzzle::decrementHeuristic(void)
{
	--this->heuristicIndex;
	this->maintainValidHeuristic();
}

void	nPuzzle::maintainValidHeuristic(void)
{
	if (this->heuristicIndex < 0)
		this->heuristicIndex = 0;
	else if (this->heuristicIndex >= heuristic::size)
		this->heuristicIndex = heuristic::size - 1;
	std::cerr	<< "Heuristic set to "	<< this->heuristicIndex	<< ' '	<< heuristic::function[this->heuristicIndex].name	<< std::endl;
}

int32_t	nPuzzle::getHeuristicIndex(void) const
{
	return (this->heuristicIndex);
}

int32_t	nPuzzle::getQueueSize(void) const
{
	return (this->solver->getQueueSize());
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
		this->clearSolver();
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

bool	nPuzzle::isSolved(void) const
{
	return (this->solver->isSolved());
}

void	nPuzzle::solve()
{
TRACE_POSITION();
	this->solver->solve();
}

bool	nPuzzle::solveStep(bool allHeuristics)
{
TRACE_POSITION();
	return (this->solver->solveStep(allHeuristics));
}

int32_t	nPuzzle::getBestSolverHeuristic(void) const
{
	return (this->solver->getTopHeuristic());
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
	this->solver->printQueueStatus();
}

std::vector<const nPuzzle::State*> nPuzzle::getSolution(void) const
{
	return this->solver->getSolution();
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
	this->clearSolver();
	*this->state = *this->start;
}

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
