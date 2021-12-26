/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_kill_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:28:45 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/26 11:14:55 by tnishina         ###   ########.fr       */
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
		kill(config->dr_pids[i], SIGKILL);
		i++;
	}
}

void
	ft_start_processes(t_philo *philos, sem_t **forks, sem_t **waiter,
	t_config *config)
{
	int			i;

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
			exit(ft_loop_philo(&philos[i]));
		config->dr_pids[i] = fork();
		if (config->dr_pids[i] < 0)
		{
			ft_kill_processes(i, config);
			kill(config->philo_pids[i], SIGKILL);
			ft_clear_sems(*forks, *waiter);
			ft_exit_with_error();
		}
		if (!config->dr_pids[i])
			exit(ft_monitor_philo(&philos[i]));
		i++;
	}
}
