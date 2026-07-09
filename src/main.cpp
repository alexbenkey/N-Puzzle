/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:52:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/07/09 19:03:07 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzleHeader.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "Starting the nPuzzle program..." << std::endl;
	nPuzzle puzzle = parse();
	return (0);
}
