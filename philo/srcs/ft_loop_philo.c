/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:37:18 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 10:50:03 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void
	find_forks(t_fork *right_fork, t_fork *left_fork, const t_philo *philo)
{
	right_fork->fork_lock = &(philo->config->forks[philo->philo_id - 1]);
	right_fork->is_taken
		= &(philo->config->are_forks_taken[philo->philo_id - 1]);
	if (philo->philo_id < philo->config->num_of_philos)
	{
		left_fork->fork_lock = &(philo->config->forks[philo->philo_id]);
		left_fork->is_taken
			= &(philo->config->are_forks_taken[philo->philo_id]);
	}
	else
	{
		left_fork->fork_lock = &(philo->config->forks[0]);
		left_fork->is_taken = &(philo->config->are_forks_taken[0]);
	}
}

t_bool
	ft_is_loop_end(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&(philo->config->screen_lock));
	res = philo->config->is_dead || philo->config->is_completed;
	pthread_mutex_unlock(&(philo->config->screen_lock));
	return (res);
}

void
	*ft_loop_philo(void *arg)
{
	t_philo	*philo;
	t_fork	right_fork;
	t_fork	left_fork;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(200);
	find_forks(&right_fork, &left_fork, philo);
	if (philo->config->num_of_philos == 1)
	{
		ft_take_a_fork(&right_fork);
		ft_print_log(philo, MESSAGE_TO_TAKE_A_FORK);
		ft_drop_a_fork(&right_fork);
		return ((void *)EXIT_SUCCESS);
	}
	while (!ft_is_loop_end(philo))
	{
		ft_take_forks(philo, &right_fork, &left_fork);
		ft_eat_spaghetti(philo);
		ft_drop_forks(&right_fork, &left_fork);
		ft_sleep_tight(philo);
		ft_think_deep(philo);
	}
	return ((void *)EXIT_SUCCESS);
}
