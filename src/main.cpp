/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/23 21:35:29 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "displayNPuzzle.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle	puzzle;

	puzzle.parse(std::cin);
	displayNPuzzle(&puzzle);
	return (0);
}
