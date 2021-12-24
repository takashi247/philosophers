/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 01:46:37 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 11:36:31 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	(*config)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ((*config)->num_of_philos));
	(*config)->are_forks_taken = (t_bool *)malloc(sizeof(t_bool)
			* ((*config)->num_of_philos));
	(*config)->are_meals_completed = (t_bool *)malloc(sizeof(t_bool)
			* ((*config)->num_of_philos));
	if (!((*config)->forks) || !((*config)->are_forks_taken)
		|| !((*config)->are_meals_completed))
	{
		ft_clear_config(config);
		return (FALSE);
	}
	memset((*config)->are_forks_taken, 0, sizeof(t_bool)
		* ((*config)->num_of_philos));
	memset((*config)->are_meals_completed, 0, sizeof(t_bool)
		* ((*config)->num_of_philos));
	return (TRUE);
}

static t_bool
	init_mutexes(t_config **config)
{
	int	i;

	i = 0;
	while (i < (*config)->num_of_philos)
	{
		if (pthread_mutex_init(&((*config)->forks[i]), NULL))
		{
			ft_destroy_forks(*config, i);
			ft_clear_config(config);
			return (FALSE);
		}
		i++;
	}
	if (pthread_mutex_init(&((*config)->screen_lock), NULL))
	{
		ft_destroy_forks(*config, (*config)->num_of_philos);
		ft_clear_config(config);
		return (FALSE);
	}
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
	if (!init_mutexes(config))
		return (FALSE);
	return (TRUE);
}
