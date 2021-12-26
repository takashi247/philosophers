/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_kill_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:28:45 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 21:38:40 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_kill_processes(int num_of_processes, t_config *config)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		kill(config->philo_pids[i], SIGKILL);
		i++;
	}
}

void
	ft_start_processes(t_philo *philos, sem_t **forks, sem_t **waiter,
	t_config *config)
{
	int			i;
	pthread_t	th_philo;
	pthread_t	th_dr;

	i = 0;
	while (i < config->num_of_philos)
	{
		config->philo_pids[i] = fork();
		if (config->philo_pids[i] < 0)
		{
			ft_kill_processes(i, config);
			ft_clear_sems(*forks, *waiter);
			ft_exit_with_error();
		}
		if (!config->philo_pids[i])
		{
			ft_start_sem_n_ths(&philos[i], &th_philo, &th_dr);
			ft_stop_sem_n_ths(&philos[i], th_philo, th_dr);
		}
		i++;
	}
}
