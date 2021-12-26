/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:37:18 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 23:30:02 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool
	ft_is_loop_end(t_philo *philo)
{
	t_bool	res;

	sem_wait(philo->waiter);
	res = philo->config->is_dead || philo->config->is_completed;
	sem_post(philo->waiter);
	return (res);
}

void
	*ft_loop_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_open_sems(philo);
	if (philo->philo_id % 2 == 0)
		usleep(200);
	if (philo->config->num_of_philos == 1)
	{
		ft_take_a_fork(philo->forks);
		ft_print_log(philo, MESSAGE_TO_TAKE_A_FORK);
		ft_drop_a_fork(philo->forks);
		return ((void *)EXIT_SUCCESS);
	}
	while (!ft_is_loop_end(philo))
	{
		ft_take_forks(philo);
		ft_eat_spaghetti(philo);
		ft_drop_forks(philo);
		ft_sleep_tight(philo);
		ft_think_deep(philo);
	}
	ft_clear_sems(philo->forks, philo->waiter);
	return ((void *)EXIT_SUCCESS);
}
