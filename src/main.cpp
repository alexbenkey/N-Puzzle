/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/17 12:55:54 by avon-ben         ###   ########.fr       */
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
	displayNPuzzle(puzzle);
	delete puzzle;
	return (0);
}
