/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:29:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/10 17:45:37 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "npuzzle.hpp"

#include <string>	// std::string	std::getline()
#include <iostream>	// std::cin

#include <sstream>	// std::istringstream
#include <vector>	// std::vector
#include <stdexcept>
#include <cctype>	// std::isspace, std::isdigit
#include <memory>	// std::unique_ptr

#include "nPuzzle.hpp"

static bool				emptyLine(const std::string &line);
static bool				validLine(const std::string &line);
static std::unique_ptr<nPuzzle>	createPuzzle(const std::string &line);
static std::vector<int>	convertLineToNumbers(const std::string& line);

nPuzzle *parse(nPuzzle *&puzzle)
{
	std::string	line;

	if (puzzle != NULL)
	{
		return NULL;
	}

	try
	{
		while (std::getline(std::cin, line))
		{
			if (emptyLine(line))
				continue;
			if (!validLine(line))
				throw std::runtime_error("Invalid puzzle size line: " + line);
			break;
		}

		std::unique_ptr<nPuzzle> tmp_puzzle = createPuzzle(line);
		int32_t row = 0;
		while (std::getline(std::cin, line))
		{
			if (!validLine(line) || emptyLine(line))
				throw std::runtime_error("Invalid puzzle row line: " + line);
			tmp_puzzle->setRow(row++, convertLineToNumbers(line));
		}
		puzzle = tmp_puzzle.release();
		puzzle->storeStartState();
	}
	catch (const std::exception &)
	{
		return NULL;
	}
	return puzzle;
}

static bool	emptyLine(const std::string &line)
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size && std::isspace(static_cast<unsigned char>(line[i])))
		++i;
	return (i == size || line[i] == '#');
}

static bool	validLine(const std::string &line)
{
	size_t	i = 0;
	size_t	size = line.size();

	while (i < size
		&& (std::isspace(static_cast<unsigned char>(line[i]))
			|| std::isdigit(static_cast<unsigned char>(line[i]))))
		++i;
	return (i == size || line[i] == '#');
}

static std::unique_ptr<nPuzzle> createPuzzle(const std::string &line)
{
	std::vector<int> numbers = convertLineToNumbers(line);

	if (numbers.size() == 1 && numbers[0] > 0)
		return std::unique_ptr<nPuzzle>(new nPuzzle(numbers[0]));
	if (numbers.size() == 2 && numbers[0] > 0 && numbers[1] > 0)
		return std::unique_ptr<nPuzzle>(new nPuzzle(numbers[0], numbers[1]));
	throw std::runtime_error(
		"Invalid puzzle size line: expected 1 or 2 positive integers");
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
