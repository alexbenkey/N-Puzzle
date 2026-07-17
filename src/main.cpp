/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/17 14:18:29 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleHeader.hpp"
#include "displayNPuzzle.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle *puzzle = NULL;
	if (parse(puzzle) == NULL)
	{
		std::cerr << "Failed to parse puzzle" << std::endl;
		return (1);
	}
	puzzle->calculateHeuristic();
	puzzle->storeStartState();
	displayNPuzzle(puzzle);
	delete puzzle;
	return (0);
}
