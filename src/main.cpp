/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/17 16:01:59 by avon-ben         ###   ########.fr       */
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
