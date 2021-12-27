/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_kill_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:28:45 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 12:57:41 by tnishina         ###   ########.fr       */
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
		kill(config->philo_pids[i], SIGTERM);
		i++;
	}
}

static void
	start_simulation(t_philo *philo)
{
	pthread_t	thr;

	if (pthread_create(&thr, NULL, ft_loop_philo, philo))
	{
		ft_putstr_fd(PTHREAD_ERR_MSG, STDERR_FILENO);
		ft_exit_with_error();
	}
	pthread_detach(thr);
	exit(ft_monitor_philo(philo));
}

void
	ft_start_processes(t_philo *philos, t_config *config)
{
	int			i;

	i = 0;
	while (i < config->num_of_philos)
	{
		config->philo_pids[i] = fork();
		if (config->philo_pids[i] < 0)
		{
			ft_kill_processes(i, config);
			ft_clear_sems(config);
			ft_exit_with_error();
		}
		if (config->philo_pids[i] == CHILD_PROCESS)
			start_simulation(&philos[i]);
		i++;
	}
}
