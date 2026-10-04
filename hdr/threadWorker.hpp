/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadWorker.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 14:31:13 by othello           #+#    #+#             */
/*   Updated: 2026/10/04 13:59:12 by avon-ben         ###   ########.fr       */
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
		void	pauseAndWait(void);
		State	getState(void) const;
		void	run(void);

	private:
		std::function<void()>	function;
		mutable std::mutex		internalMutex;
		ThreadWorker::State		state;
		std::condition_variable	condition;
		bool					active = false;
		std::thread				thread;
};

#endif
