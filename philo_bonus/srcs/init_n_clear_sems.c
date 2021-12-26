/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_clear_sems.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:08:22 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 23:47:43 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_clear_sems(sem_t *forks, sem_t *waiter)
{
	if (forks != SEM_FAILED)
	{
		sem_close(forks);
		sem_unlink(SEM4FORKS);
	}
	if (waiter != SEM_FAILED)
	{
		sem_close(waiter);
		sem_unlink(SEM4WAITER);
	}
}

void
	ft_init_sems(sem_t **forks, sem_t **waiter, t_config **config)
{
	sem_unlink(SEM4FORKS);
	sem_unlink(SEM4WAITER);
	(*forks) = sem_open(SEM4FORKS, O_CREAT|O_EXCL, S_IRWXU, (*config)->num_of_philos);
	(*waiter) = sem_open(SEM4WAITER, O_CREAT|O_EXCL, S_IRWXU, NUM_OF_WAITER);
	if (*forks == SEM_FAILED || *waiter == SEM_FAILED)
	{
		ft_clear_sems(*forks, *waiter);
		ft_exit_with_error();
	}
}
