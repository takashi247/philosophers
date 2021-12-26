/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:49:08 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/26 11:09:20 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static t_bool
	is_monitor_loop_end(t_philo *philo, sem_t *waiter)
{
	t_bool	res;

	sem_wait(waiter);
	res = philo->config->is_dead || philo->config->is_completed;
	sem_post(waiter);
	return (res);
}

int
	ft_monitor_philo(t_philo *philo)
{
	t_config	*config;
	long		current_time;
	long		time_to_die;
	sem_t		*waiter;

	waiter = sem_open(SEM4WAITER, 0);
	config = philo->config;
	time_to_die = (long)philo->config->time_to_die;
	while (!is_monitor_loop_end(philo, waiter))
	{
		ft_sleep_in_millisecond(MONITORING_INTERVAL_IN_MS);
		sem_wait(waiter);
		current_time = ft_get_time();
		if (current_time - philo->last_meal_time >= time_to_die
			&& !config->is_dead)
		{
			config->is_dead = TRUE;
			ft_print_msg(MESSAGE_TO_DIE, current_time, philo->philo_id);
		}
		if (check_meals_completed(philo))
			config->is_completed = TRUE;
		sem_post(waiter);
	}
	sem_close(waiter);
	return (EXIT_SUCCESS);
}
