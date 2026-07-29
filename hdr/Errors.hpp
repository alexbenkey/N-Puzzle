/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 12:38:06 by othello           #+#    #+#             */
/*   Updated: 2026/07/29 21:23:11 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# define	DEBUG_SILENT	0
# define	DEBUG_ERROR	1
# define	DEBUG_WARNING	2
# define	DEBUG_INFO	3
# define	DEBUG_DEBUG	4
# define	DEBUG_TRACE	5
# define	DEBUG_ALL	6

# if DEBUG >= DEBUG_ERROR
#  define TRACE_POSITION(fmt, ...) \
do { \
	std::fprintf(stderr, \
		C_DGRAY "%s" C_RESET "::%s[%i] " fmt "\n", \
		__FILE__, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)
#else
    #define TRACE_POSITION(...) ((void)0)
#endif

#endif
