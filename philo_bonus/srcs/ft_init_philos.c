/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:26:39 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo
	*create_philos(t_config *config)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * config->num_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->num_of_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].last_meal_time = ft_get_time();
		philos[i].num_of_meals_completed = 0;
		philos[i].is_meal_completed = &(config->are_meals_completed[i]);
		philos[i].config = config;
		i++;
	}
	return (philos);
}

static void
	clear_ths_n_philos(pthread_t **ths_philo, pthread_t **ths_dr,
	t_philo **philos)
{
	if (*ths_philo)
	{
		free(*ths_philo);
		*ths_philo = NULL;
	}
	if (*ths_dr)
	{
		free(*ths_dr);
		*ths_dr = NULL;
	}
	if (*philos)
	{
		free(*philos);
		*philos = NULL;
	}
}

t_bool
	ft_init_philos(pthread_t **ths_philo, pthread_t **ths_dr, t_philo **philos,
	t_config **config)
{
	*ths_philo = (pthread_t *)malloc(sizeof(pthread_t)
			* (*config)->num_of_philos);
	*ths_dr = (pthread_t *)malloc(sizeof(pthread_t)
			* (*config)->num_of_philos);
	*philos = create_philos(*config);
	if (!(*ths_philo) || !(*ths_dr) || !(*philos))
	{
		clear_ths_n_philos(ths_philo, ths_dr, philos);
		ft_clear_config(config);
		return (FALSE);
	}
	return (TRUE);
}
