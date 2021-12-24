/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:49:08 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 16:05:23 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool
	check_meals_completed(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_of_philos)
	{
		if (!philo->config->are_meals_completed[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void
	*ft_monitor_philo(void *arg)
{
	t_philo		*philo;
	t_config	*config;
	long		current_time;
	long		time_to_die;

	philo = (t_philo *)arg;
	config = philo->config;
	time_to_die = (long)philo->config->time_to_die;
	while (!ft_is_loop_end(philo))
	{
		ft_sleep_in_millisecond(MONITORING_INTERVAL_IN_MS);
		pthread_mutex_lock(&(config->screen_lock));
		current_time = ft_get_time();
		if (current_time - philo->last_meal_time >= time_to_die
			&& !config->is_dead)
		{
			config->is_dead = TRUE;
			ft_print_msg(MESSAGE_TO_DIE, current_time, philo->philo_id);
		}
		if (check_meals_completed(philo))
			config->is_completed = TRUE;
		pthread_mutex_unlock(&(config->screen_lock));
	}
	return ((void *)EXIT_SUCCESS);
}
