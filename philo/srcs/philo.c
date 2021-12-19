/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/19 23:30:55 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long
	get_time(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * THOUSAND;
	milliseconds += tv.tv_usec / THOUSAND;
	return (milliseconds);
}

void
	print_status(int philo_id, char *msg, pthread_mutex_t *screen)
{
	if (screen)
		pthread_mutex_lock(screen);
	printf(msg, get_time(), philo_id);
	if (screen)
		pthread_mutex_unlock(screen);
}

void
	*monitor_philo(void *arg)
{
	(void)arg;
	return ((void *)EXIT_SUCCESS);
}

void
	take_fork(int id, pthread_mutex_t *fork, pthread_mutex_t *screen)
{
	pthread_mutex_lock(fork);
	print_status(id, MESSAGE_TO_TAKE_FORK, screen);
}

void
	take_fork_n_eat(int id, pthread_mutex_t *fork, pthread_mutex_t *screen)
{

	pthread_mutex_lock(fork);
	pthread_mutex_lock(screen);
	print_status(id, MESSAGE_TO_TAKE_FORK, NULL);
	print_status(id, MESSAGE_TO_EAT, NULL);
	pthread_mutex_unlock(screen);
}

void
	drop_forks(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void
	sleep_in_millisecond(unsigned int micro_sec)
{
	const long	start_time = get_time();
	const long	time_to_sleep = (long)micro_sec;

	while (get_time() - start_time < time_to_sleep)
	{
		micro_sec /= 2;
		usleep(micro_sec);
	}
}

void
	*loop_philo(void *arg)
{
	const t_philo	*philo = (t_philo *)arg;
	pthread_mutex_t	*screen;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

	screen = &(philo->config->screen);
	right_fork = &(philo->config->forks[philo->philo_id - 1]);
	if (philo->philo_id < philo->config->num_of_philos)
		left_fork = &(philo->config->forks[philo->philo_id]);
	else
		left_fork = &(philo->config->forks[0]);
	if (philo->philo_id % 2 == 0)
		usleep(200);
	take_fork(philo->philo_id, right_fork, screen);
	take_fork_n_eat(philo->philo_id, left_fork, screen);
	sleep_in_millisecond(philo->config->time_to_eat);
	drop_forks(right_fork, left_fork);
	print_status(philo->philo_id, MESSAGE_TO_SLEEP, screen);
	sleep_in_millisecond(philo->config->time_to_sleep);
	print_status(philo->philo_id, MESSAGE_TO_THINK, screen);
	return ((void *)EXIT_SUCCESS);
}

t_bool
	ft_init_philo(t_config *config, int ac, char **av)
{
	int	i;
	int	ret;

	if (!ft_isposint(av[1]) || !ft_isposint(av[2]) || !ft_isposint(av[3])
		|| !ft_isposint(av[4]) || (ac == 6 && !ft_isposint(av[5])))
		return (FALSE);
	config->num_of_philos = ft_atoi_s(av[1]);
	config->time_to_die = (unsigned int)ft_atoi_s(av[2]);
	config->time_to_eat = (unsigned int)ft_atoi_s(av[3]);
	config->time_to_sleep = (unsigned int)ft_atoi_s(av[4]);
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
	ret = pthread_mutex_init(&(config->screen), NULL);
	if (ret != 0)
		return (FALSE);
	return (TRUE);
}

int
	main(int ac, char **av)
{
	int				ret[2];
	pthread_t		ths[MAX_NUM_THREADS];
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
		ret[0] = pthread_create(&ths[i * 2], NULL, loop_philo, &philos[i]);
		ret[1] = pthread_create(&ths[i * 2 + 1], NULL, monitor_philo, &philos[i]);
		if (ret[0] != 0 || ret[1] != 0)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < config.num_of_philos)
	{
		pthread_join(ths[i * 2], NULL);
		pthread_join(ths[i * 2 + 1], NULL);
		i++;
	}
	i = 0;
	while (i < config.num_of_philos)
	{
		pthread_mutex_destroy(&(config.forks[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}
