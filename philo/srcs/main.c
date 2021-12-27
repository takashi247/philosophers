/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 11:15:04 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
// function for leak check

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}
*/

void
	ft_destroy_forks(t_config *config, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&(config->forks[i]));
		i++;
	}
}

void
	ft_clear_config(t_config **config)
{
	if ((*config)->forks)
	{
		free((*config)->forks);
		(*config)->forks = NULL;
	}
	if ((*config)->are_forks_taken)
	{
		free((*config)->are_forks_taken);
		(*config)->are_forks_taken = NULL;
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
	clean_up_all(pthread_t **ths_philo, pthread_t **ths_dr, t_philo **philos,
	t_config **config)
{
	ft_destroy_forks(*config, (*config)->num_of_philos);
	pthread_mutex_destroy(&((*config)->screen_lock));
	free(*ths_philo);
	*ths_philo = NULL;
	free(*ths_dr);
	*ths_dr = NULL;
	free(*philos);
	*philos = NULL;
	ft_clear_config(config);
}

static int
	exit_with_error(void)
{
	ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int
	main(int ac, char **av)
{
	pthread_t		*ths_philo;
	pthread_t		*ths_dr;
	t_config		*config;
	t_philo			*philos;

	if (ac <= 4 || 7 <= ac || !ft_init_config(&config, ac, av))
		return (exit_with_error());
	if (!ft_init_philos(&ths_philo, &ths_dr, &philos, &config))
		return (exit_with_error());
	if (ft_start_threads(ths_philo, ths_dr, philos, config))
		ft_join_threads(ths_philo, ths_dr, config->num_of_philos);
	clean_up_all(&ths_philo, &ths_dr, &philos, &config);
	return (EXIT_SUCCESS);
}
