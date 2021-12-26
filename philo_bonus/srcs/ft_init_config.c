/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 01:46:37 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/26 10:59:17 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
	set_config(t_config *config, int ac, char **av)
{
	config->num_of_philos = ft_atoi_s(av[1]);
	config->time_to_die = (unsigned int)ft_atoi_s(av[2]);
	config->time_to_eat = (unsigned int)ft_atoi_s(av[3]);
	config->time_to_sleep = (unsigned int)ft_atoi_s(av[4]);
	config->is_dead = FALSE;
	config->is_completed = FALSE;
	if (ac == 6)
		config->num_of_must_eat = ft_atoi_s(av[5]);
	else
		config->num_of_must_eat = NO_NUM_OF_MUST_EAT;
}

static t_bool
	malloc_config_params(t_config **config)
{
	(*config)->are_meals_completed = (t_bool *)malloc(sizeof(t_bool)
			* ((*config)->num_of_philos));
	(*config)->philo_pids = (pid_t *)malloc(sizeof(pid_t)
			* ((*config)->num_of_philos));
	(*config)->dr_pids = (pid_t *)malloc(sizeof(pid_t)
			* ((*config)->num_of_philos));
	if (!((*config)->are_meals_completed) || !((*config)->philo_pids)
		|| !((*config)->dr_pids))
	{
		ft_clear_config(config);
		return (FALSE);
	}
	memset((*config)->are_meals_completed, 0, sizeof(t_bool)
		* ((*config)->num_of_philos));
	return (TRUE);
}

t_bool
	ft_init_config(t_config **config, int ac, char **av)
{
	if (!ft_isposint(av[1]) || !ft_isposint(av[2]) || !ft_isposint(av[3])
		|| !ft_isposint(av[4]) || (ac == 6 && !ft_isposint(av[5])))
		return (FALSE);
	*config = (t_config *)malloc(sizeof(t_config));
	if (!(*config))
		return (FALSE);
	set_config(*config, ac, av);
	if ((*config)->num_of_philos > MAX_NUM_THREADS)
		return (FALSE);
	if (!malloc_config_params(config))
		return (FALSE);
	return (TRUE);
}
