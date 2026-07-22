/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/22 18:21:16 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "displayNPuzzle.hpp"
#include <iostream>

#include "Test.hpp"

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle	puzzle;

	puzzle.parse(std::cin);
	// displayNPuzzle(&puzzle);
	Test	test;
	Test::Child	child;
	return (0);
}
