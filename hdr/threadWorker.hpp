/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadWorker.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othello <othello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 14:31:13 by othello           #+#    #+#             */
/*   Updated: 2026/09/03 21:03:24 by othello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADWORKER_HPP
# define THREADWORKER_HPP

# include <thread>	// std::thread
# include <mutex>	// std::mutex
# include <condition_variable>	// std::condition_variable
# include <functional>	// std::function

class ThreadWorker
{
	public:
		enum class State
		{
			STOP,
			IDLE,
			RUNONCE,
			RUNNING,
		};
		mutable std::mutex	mutex;

		ThreadWorker(std::function<void()> f);
		~ThreadWorker(void);

		void	setState(State state);
		State	getState(void) const;
		void	run(void);

	private:
		std::thread				thread;
		std::function<void()>	function;
		mutable std::mutex		internalMutex;
		ThreadWorker::State		state;
		std::condition_variable	condition;
};

#endif
