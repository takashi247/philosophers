/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_n_join_ths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:35:21 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_join_threads(pthread_t *ths_philo, pthread_t *ths_dr, int num_of_ths)
{
	int	i;

	i = 0;
	while (i < num_of_ths)
	{
		pthread_join(ths_philo[i], NULL);
		pthread_join(ths_dr[i], NULL);
		i++;
	}
}

t_bool
	ft_start_threads(pthread_t *ths_philo, pthread_t *ths_dr, t_philo *philos,
	t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_of_philos)
	{
		if (pthread_create(&ths_philo[i], NULL, ft_loop_philo, &philos[i]))
		{
			pthread_mutex_lock(&(config->screen_lock));
			config->is_completed = TRUE;
			pthread_mutex_unlock(&(config->screen_lock));
			ft_join_threads(ths_philo, ths_dr, i);
			return (FALSE);
		}
		if (pthread_create(&ths_dr[i], NULL, ft_monitor_philo, &philos[i]))
		{
			pthread_mutex_lock(&(config->screen_lock));
			config->is_completed = TRUE;
			pthread_mutex_unlock(&(config->screen_lock));
			ft_join_threads(ths_philo, ths_dr, i);
			pthread_join(ths_philo[i], NULL);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
