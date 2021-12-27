/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:57:08 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 13:40:34 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_wait_processes(t_config *config)
{
	int			i;

	i = 0;
	while (i < config->num_of_philos)
	{
		sem_wait(config->sem_end);
		i++;
	}
	ft_kill_processes(config->num_of_philos, config);
}
