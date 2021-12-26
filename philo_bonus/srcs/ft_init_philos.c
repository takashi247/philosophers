/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:26:39 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 17:01:50 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo
	*ft_create_philos(t_config *config)
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
