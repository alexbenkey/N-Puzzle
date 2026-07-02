/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Display.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/02 17:58:28 by ohengelm      #+#    #+#                 */
/*   Updated: 2026/07/02 17:58:28 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include "../assets/raylib/src/raylib.h"

class Display
{
	private:
		int			rows;
		int			cols;
		Rectangle	Frame;
		Rectangle	tile;

	protected:

	public:
		Display(void);
		Display(const Display &src);
		~Display(void);

		void	adjustScale();
		void	render();

		Display	&operator=(const Display &src);
};

#endif
