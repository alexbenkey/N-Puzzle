/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:29:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/09 17:25:51 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "npuzzle.hpp"

#include <string>	// std::string	std::getline()
#include <iostream>	// std::cin

#include <sstream>	// std::istringstream
#include <vector>	// std::vector
#include <stdexcept>

#include "nPuzzle.hpp"

static bool				emptyLine(const std::string &line);
static bool				validLine(const std::string &line);
static nPuzzle 		createPuzzle(const std::string &line);
static std::vector<int>	convertLineToNumbers(const std::string& line);

nPuzzle	parse()
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (!emptyLine(line))
			break;
	}
	nPuzzle puzzle = createPuzzle(line);
	int32_t row = 0;
	while (std::getline(std::cin, line))
	{
		// if (!validLine(line))
		// 	throw std::runtime_error("Invalid line: " + line);
		if (!emptyLine(line) && validLine(line))
			puzzle.setRow(row++, convertLineToNumbers(line));
	}

	// if (!puzzle)
		//throw std::runtime_error("No puzzle created from input");
		
	puzzle.printPuzzle();
	// puzzle.printTarget();
	// puzzle.printEmptyTilePos();
	return puzzle;
}

static bool	emptyLine(const std::string &line)
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size && std::isspace(line[i]))
		++i;
	return (i == size || line[i] == '#');
}

static bool	validLine(const std::string &line)
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size && (std::isspace(line[i]) || std::isdigit(line[i])))
		++i;
	return (i == size || line[i] == '#');
}

static nPuzzle createPuzzle(const std::string &line)
{
	std::vector<int> numbers = convertLineToNumbers(line);;

	if (numbers.size() == 1)
		return nPuzzle(numbers[0]);
	if (numbers.size() == 2)
		return nPuzzle(numbers[0], numbers[1]);
	throw std::runtime_error("Invalid puzzle size line: expected 1 or 2 integers");
}

static std::vector<int>	convertLineToNumbers(const std::string& line)
{
	std::istringstream	iss(line);
	int					x;
	std::vector<int>	numbers;

	while (iss >> x)
		numbers.push_back(x);
	return (numbers);
}
