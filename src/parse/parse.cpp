/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:29:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/10 18:43:31 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>	// std::string	std::getline()
#include <iostream>	// std::cout	std::cin

void	parse()
{
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.at(0) != '#')
			std::cout	<< line	<< '\n';
	}
	std::cout	<< std::flush;
}
