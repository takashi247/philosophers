/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 14:32:26 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// // function for leak check

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo_bonus");
// }

void
	ft_clear_config(t_config **config)
{
	if ((*config)->philo_pids)
	{
		free((*config)->philo_pids);
		(*config)->philo_pids = NULL;
	}
	free(*config);
	*config = NULL;
}

static void
	clean_up_all(t_philo **philos, t_config **config)
{
	free(*philos);
	*philos = NULL;
	ft_clear_sems(*config);
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
	t_config	*config;
	t_philo		*philos;

	config = NULL;
	if (ac <= 4 || 7 <= ac || !ft_init_config(&config, ac, av))
		ft_exit_with_error();
	ft_init_sems(&config);
	philos = ft_create_philos(config);
	if (!philos)
	{
		ft_clear_sems(config);
		ft_exit_with_error();
	}
	ft_start_processes(philos, config);
	ft_wait_processes(config);
	clean_up_all(&philos, &config);
	return (EXIT_SUCCESS);
}
