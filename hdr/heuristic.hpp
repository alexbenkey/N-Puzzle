/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:13:17 by othello           #+#    #+#             */
/*   Updated: 2026/07/23 14:21:14 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURTISTIC_HPP

# include <aio.h>	// int32_t

# include "nPuzzleState.hpp"

namespace heuristic
{
	struct List
	{
		const char*	name;
		int32_t	(*f)(const nPuzzleState*, const nPuzzleState*);
	};

	extern const List		function[];
	extern const int32_t	size;

	int32_t	getHeuristic(int32_t h, const nPuzzleState* current, const nPuzzleState* target);
}

#endif
