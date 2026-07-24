/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:13:17 by othello           #+#    #+#             */
/*   Updated: 2026/07/23 21:37:22 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURTISTIC_HPP

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
