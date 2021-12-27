/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:49:08 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 13:41:41 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_end_simulation(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->config->num_of_philos)
	{
		sem_post(philo->config->sem_end);
		i++;
	}
}

int
	ft_monitor_philo(t_philo *philo)
{
	t_config	*config;
	long		current_time;
	long		time_to_die;

	config = philo->config;
	time_to_die = (long)philo->config->time_to_die;
	while (1)
	{
		ft_sleep_in_millisecond(MONITORING_INTERVAL_IN_MS);
		sem_wait(philo->config->sem_screen);
		current_time = ft_get_time();
		if (current_time - philo->last_meal_time >= time_to_die)
		{
			philo->is_end = TRUE;
			ft_print_msg(MESSAGE_TO_DIE, current_time, philo->philo_id);
			ft_end_simulation(philo);
			break ;
		}
		sem_post(philo->config->sem_screen);
	}
	return (EXIT_SUCCESS);
}
