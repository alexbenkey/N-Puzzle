/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:13:17 by othello           #+#    #+#             */
/*   Updated: 2026/07/31 16:55:29 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include <aio.h>	// int32_t

# include "nPuzzle.Board.hpp"

namespace heuristic
{
	struct List
	{
		const char*	name;
		int32_t	(*f)(const nPuzzle::Board&, const nPuzzle::Board&);
	};

	extern const List		function[];
	extern const int32_t	size;

	int32_t	getHeuristic(int32_t h, const nPuzzle::Board& current, const nPuzzle::Board& target);
}

#endif
