/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/18 17:15:20 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	*loop_philo(void *arg)
{
	const t_philo	*philo = (t_philo *)arg;
	struct timeval	tv;
	double			time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%.0f philosopher %d is created\n", time_in_mill, philo->philo_id);
	return ((void *)EXIT_SUCCESS);
}

t_bool
	ft_init_philo(t_config *config, int ac, char **av)
{
	int	i;
	int	ret;

	if (!ft_isint(av[1]) || !ft_isint(av[2]) || !ft_isint(av[3])
		|| !ft_isint(av[4]))
		return (FALSE);
	if (ac == 6 && !ft_isint(av[5]))
		return (FALSE);
	config->num_of_philos = ft_atoi_s(av[1]);
	config->time_to_die = ft_atoi_s(av[2]);
	config->time_to_eat = ft_atoi_s(av[3]);
	config->time_to_sleep = ft_atoi_s(av[4]);
	if (ac == 6)
		config->num_of_must_eat = ft_atoi_s(av[5]);
	if (config->num_of_philos > MAX_NUM_THREADS / 2)
		return (FALSE);
	i = 0;
	while (i < config->num_of_philos)
	{
		ret = pthread_mutex_init(&(config->forks[i]), NULL);
		if (ret != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	main(int ac, char **av)
{
	int				ret[2];
	pthread_t		threads[MAX_NUM_THREADS];
	t_config		config;
	t_philo			philos[MAX_NUM_THREADS / 2];
	int				i;

	if (ac <= 4 || 7 <= ac || !ft_init_philo(&config, ac, av))
		return (EXIT_FAILURE);
	i = 0;
	while (i < config.num_of_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].config = &config;
		ret[0] = pthread_create(&threads[i * 2], NULL, loop_philo, &philos[i]);
		ret[1] = pthread_create(&threads[i * 2 + 1], NULL, loop_philo, &philos[i]);
		usleep(10000);
		if (ret[0] != 0 || ret[1] != 0)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < config.num_of_philos)
	{
		pthread_join(threads[i * 2], NULL);
		pthread_join(threads[i * 2 + 1], NULL);
		pthread_mutex_destroy(&(config.forks[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}
