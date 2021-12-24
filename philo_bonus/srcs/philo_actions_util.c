/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:45:07 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_take_a_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->fork_lock);
	*(fork->is_taken) = TRUE;
}

void
	ft_drop_a_fork(t_fork *fork)
{
	*(fork->is_taken) = FALSE;
	pthread_mutex_unlock(fork->fork_lock);
}

void
	ft_sleep_in_millisecond(unsigned int micro_sec)
{
	const long		start_time = ft_get_time();
	const long		time_to_sleep = (long)micro_sec;
	unsigned int	usleep_time;

	while (ft_get_time() - start_time < time_to_sleep)
	{
		usleep_time = INITIAL_USLEEP_VALUE;
		usleep_time /= 2;
		usleep(usleep_time);
	}
}

long
	ft_get_time(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * THOUSAND;
	milliseconds += tv.tv_usec / THOUSAND;
	return (milliseconds);
}
