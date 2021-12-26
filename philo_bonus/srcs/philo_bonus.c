/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 17:49:58 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
// function for leak check

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}
*/

void
	wait_processes(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philos)
	{
		waitpid(config->philo_pids[i], NULL, 0);
		i++;
	}
}

void
	ft_clear_config(t_config **config)
{
	if ((*config)->philo_pids)
	{
		free((*config)->philo_pids);
		(*config)->philo_pids = NULL;
	}
	if ((*config)->are_meals_completed)
	{
		free((*config)->are_meals_completed);
		(*config)->are_meals_completed = NULL;
	}
	free(*config);
	*config = NULL;
}

static void
	clean_up_all(t_philo **philos, sem_t *fork, sem_t *waiter,
	t_config **config)
{
	free(*philos);
	*philos = NULL;
	sem_close(fork);
	sem_close(waiter);
	ft_clear_config(config);
}

void
	ft_exit_with_error(void)
{
	ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int
	main(int ac, char **av)
{
	sem_t		*forks;
	sem_t		*waiter;
	t_config	*config;
	t_philo		*philos;

	config = NULL;
	if (ac <= 4 || 7 <= ac || !ft_init_config(&config, ac, av))
		ft_exit_with_error();
	philos = ft_create_philos(config);
	if (!philos)
		ft_exit_with_error();
	ft_init_sems(&forks, &waiter, &config);
	ft_start_processes(philos, &forks, &waiter, config);
	wait_processes(config);
	clean_up_all(&philos, forks, waiter, &config);
	return (EXIT_SUCCESS);
}
