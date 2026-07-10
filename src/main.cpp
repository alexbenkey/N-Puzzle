/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/10 16:58:13 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleHeader.hpp"
#include "displayNPuzzle.hpp"
#include <iostream>

void simulate(nPuzzle &puzzle); 

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle *puzzle = NULL;
	if (parse(puzzle) == NULL)
	{
		std::cerr << "Failed to parse puzzle" << std::endl;
		return (1);
	}
	simulate(*puzzle);
	displayNPuzzle(puzzle);
	delete puzzle;
	return (0);
}

void simulate(nPuzzle &puzzle)
{
	puzzle.printPuzzle();
	puzzle.printTarget();
	puzzle.printEmptyTilePos();
	std::cout << "Simulating puzzle moves..." << std::endl;
	// Example simulation: Move the empty tile up, down, left, and right
	puzzle.moveUp();
	puzzle.printPuzzle();
	puzzle.moveDown();
	puzzle.printPuzzle();
	puzzle.moveLeft();
	puzzle.printPuzzle();
	puzzle.moveRight();
	puzzle.printPuzzle();
}
