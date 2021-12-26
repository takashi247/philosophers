/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_stop_sem_n_ths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 10:07:01 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/26 09:45:42 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
	set_as_completed(sem_t *waiter, t_config *config)
{
	sem_wait(waiter);
	config->is_completed = TRUE;
	sem_post(waiter);
}

void
	ft_open_sems(t_philo *philo)
{
	philo->forks = sem_open(SEM4FORKS, 0);
	philo->waiter = sem_open(SEM4WAITER, 0);
	if (philo->forks == SEM_FAILED || philo->waiter == SEM_FAILED)
	{
		ft_clear_sems(philo->forks, philo->waiter);
		ft_exit_with_error();
	}
}

void
	ft_start_sem_n_ths(t_philo *philo, pthread_t *th_philo, pthread_t *th_dr)
{
	if (pthread_create(th_philo, NULL, ft_loop_philo, philo))
	{
		set_as_completed(philo->forks, philo->config);
		ft_clear_sems(philo->forks, philo->waiter);
		ft_exit_with_error();
	}
	if (pthread_create(th_dr, NULL, ft_monitor_philo, philo))
	{
		set_as_completed(philo->forks, philo->config);
		ft_clear_sems(philo->forks, philo->waiter);
		pthread_join(*th_philo, NULL);
		ft_exit_with_error();
	}
}

void
	ft_stop_sem_n_ths(t_philo *philo, pthread_t th_philo, pthread_t th_dr)
{
	pthread_join(th_philo, NULL);
	pthread_join(th_dr, NULL);
	sem_close(philo->forks);
	sem_close(philo->waiter);
	exit(EXIT_SUCCESS);
}
