/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/10/04 14:18:58 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"
#include "displayNPuzzle.hpp"
#include <iostream>
#include "Errors.hpp"

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle	puzzle;

	try
	{
		puzzle.parse(std::cin);
		displayNPuzzle(&puzzle);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: "	<< e.what() << std::endl;
	}

	return (0);
}
