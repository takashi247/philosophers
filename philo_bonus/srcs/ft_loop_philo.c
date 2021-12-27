/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:37:18 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 13:43:37 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool
	ft_is_loop_end(t_philo *philo)
{
	t_bool	res;

	sem_wait(philo->config->sem_screen);
	res = philo->is_end;
	sem_post(philo->config->sem_screen);
	return (res);
}

static void
	loop_for_solo(t_philo *philo)
{
	ft_take_a_fork(philo->config->forks);
	ft_print_log(philo, MESSAGE_TO_TAKE_A_FORK);
	ft_drop_a_fork(philo->config->forks);
	while (!ft_is_loop_end(philo))
		usleep(200);
}

void
	*ft_loop_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->config->sem_screen);
	philo->last_meal_time = ft_get_time();
	sem_post(philo->config->sem_screen);
	if (philo->philo_id % 2 == 0)
		usleep(200);
	if (philo->config->num_of_philos == 1)
	{
		loop_for_solo(philo);
		return (EXIT_SUCCESS);
	}
	while (!ft_is_loop_end(philo))
	{
		ft_take_forks(philo);
		ft_eat_spaghetti(philo);
		ft_drop_forks(philo);
		ft_sleep_tight(philo);
		ft_think_deep(philo);
	}
	return (EXIT_SUCCESS);
}
