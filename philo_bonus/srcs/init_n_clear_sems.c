/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_clear_sems.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:08:22 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 09:47:02 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_clear_sems(t_config *config)
{
	if (config->forks != SEM_FAILED)
	{
		sem_close(config->forks);
		sem_unlink(SEM4FORKS);
	}
	if (config->sem_end != SEM_FAILED)
	{
		sem_close(config->sem_end);
		sem_unlink(SEM4END);
	}
	if (config->sem_screen != SEM_FAILED)
	{
		sem_close(config->sem_screen);
		sem_unlink(SEM4SCREEN);
	}
}

void
	ft_init_sems(t_config **config)
{
	sem_unlink(SEM4FORKS);
	sem_unlink(SEM4END);
	sem_unlink(SEM4SCREEN);
	(*config)->forks = sem_open(SEM4FORKS, O_CREAT | O_EXCL, S_IRWXU,
			(*config)->num_of_philos);
	(*config)->sem_end = sem_open(SEM4END, O_CREAT | O_EXCL, S_IRWXU, 0);
	(*config)->sem_screen = sem_open(SEM4SCREEN, O_CREAT | O_EXCL, S_IRWXU, 1);
	if ((*config)->forks == SEM_FAILED || (*config)->sem_end == SEM_FAILED
		|| (*config)->sem_screen == SEM_FAILED)
	{
		ft_clear_sems(*config);
		ft_exit_with_error();
	}
}
