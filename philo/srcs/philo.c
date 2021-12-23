/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/23 10:50:25 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// function for leak check

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

void
	ft_safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

char
	*create_msg(char *msg, char *str_time, char *str_id)
{
	char	*str_combined;
	char	*tmp;

	str_combined = ft_strjoin(str_time, " ");
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, str_id);
	ft_safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, " ");
	ft_safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, msg);
	ft_safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	return (str_combined);
}

t_bool
	print_msg(char *msg, long current_time, int philo_id)
{
	char	*str_time;
	char	*str_id;
	char	*str_combined;
	t_bool	res;

	res = TRUE;
	str_time = ft_convert_time2str(current_time);
	if (str_time)
		str_id = ft_itoa(philo_id);
	if (!str_time || !str_id)
	{
		if (str_time)
			ft_safe_free(&str_time);
		res = FALSE;
		return (res);
	}
	str_combined = create_msg(msg, str_time, str_id);
	if (!str_combined)
		res = FALSE;
	else
		ft_putstr_fd(str_combined, STDOUT_FILENO);
	ft_safe_free(&str_combined);
	ft_safe_free(&str_time);
	ft_safe_free(&str_id);
	return (res);
}

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
	ft_drop_forks(t_fork *right_fork, t_fork *left_fork)
{
	*(right_fork->is_taken) = FALSE;
	pthread_mutex_unlock(right_fork->fork_lock);
	*(left_fork->is_taken) = FALSE;
	pthread_mutex_unlock(left_fork->fork_lock);
}

void
	sleep_in_millisecond(unsigned int micro_sec)
{
	const long	start_time = get_time();
	const long	time_to_sleep = (long)micro_sec;

	while (get_time() - start_time < time_to_sleep)
	{
		micro_sec = INITIAL_USLEEP_VALUE;
		micro_sec /= 2;
		usleep(micro_sec);
	}
}

void
	take_a_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->fork_lock);
	*(fork->is_taken) = TRUE;
}

void
	print_log(t_philo *philo, char *msg)
{
	t_bool	res;
	long	current_time;

	pthread_mutex_lock(&(philo->config->screen_lock));
	if (!philo->config->is_dead && !philo->config->is_completed)
	{
		current_time = get_time();
		res = print_msg(msg, current_time, philo->philo_id);
		if (!res)
			philo->config->is_completed = TRUE;
		if (!ft_strncmp(msg, MESSAGE_TO_EAT, ft_strlen(MESSAGE_TO_EAT)))
			philo->last_meal_time = current_time;
	}
	pthread_mutex_unlock(&(philo->config->screen_lock));
}

void
	ft_take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	take_a_fork(right_fork);
	print_log(philo, MESSAGE_TO_TAKE_A_FORK);
	take_a_fork(left_fork);
	print_log(philo, MESSAGE_TO_TAKE_A_FORK);
}

void
	ft_eat_spaghetti(t_philo *philo)
{
	print_log(philo, MESSAGE_TO_EAT);
	sleep_in_millisecond(philo->config->time_to_eat);
}

void
	ft_sleep_tight(t_philo *philo)
{
	print_log(philo, MESSAGE_TO_SLEEP);
	sleep_in_millisecond(philo->config->time_to_sleep);
}

void
	ft_think_deep(t_philo *philo)
{
	print_log(philo, MESSAGE_TO_THINK);
}

t_bool
	ft_is_dead(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&(philo->config->screen_lock));
	res = philo->config->is_dead;
	pthread_mutex_unlock(&(philo->config->screen_lock));
	return (res);
}

t_bool
	ft_is_completed(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&(philo->config->screen_lock));
	res = philo->config->is_completed;
	pthread_mutex_unlock(&(philo->config->screen_lock));
	return (res);
}

t_bool
	ft_is_loop_end(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&(philo->config->screen_lock));
	res = philo->config->is_dead || philo->config->is_completed;
	pthread_mutex_unlock(&(philo->config->screen_lock));
	return (res);
}

void
	*loop_philo(void *arg)
{
	t_philo			*philo;
	t_fork			right_fork;
	t_fork			left_fork;

	philo = (t_philo *)arg;
	right_fork.fork_lock = &(philo->config->forks[philo->philo_id - 1]);
	right_fork.is_taken = &(philo->config->are_forks_taken[philo->philo_id - 1]);
	if (philo->philo_id < philo->config->num_of_philos)
	{
		left_fork.fork_lock = &(philo->config->forks[philo->philo_id]);
		left_fork.is_taken = &(philo->config->are_forks_taken[philo->philo_id]);
	}
	else
	{
		left_fork.fork_lock = &(philo->config->forks[0]);
		left_fork.is_taken = &(philo->config->are_forks_taken[0]);
	}
	if (philo->philo_id % 2 == 0)
		usleep(200);
	while (!ft_is_loop_end(philo))
	{
		ft_take_forks(philo, &right_fork, &left_fork);
		ft_eat_spaghetti(philo);
		ft_drop_forks(&right_fork, &left_fork);
		ft_sleep_tight(philo);
		ft_think_deep(philo);
	}
	return ((void *)EXIT_SUCCESS);
}

t_bool
	ft_init_config(t_config **config, int ac, char **av)
{
	int	i;
	int	ret;

	if (!ft_isposint(av[1]) || !ft_isposint(av[2]) || !ft_isposint(av[3])
		|| !ft_isposint(av[4]) || (ac == 6 && !ft_isposint(av[5])))
		return (FALSE);
	*config = (t_config *)malloc(sizeof(t_config));
	if (!(*config))
		return (FALSE);
	(*config)->num_of_philos = ft_atoi_s(av[1]);
	(*config)->time_to_die = (unsigned int)ft_atoi_s(av[2]);
	(*config)->time_to_eat = (unsigned int)ft_atoi_s(av[3]);
	(*config)->time_to_sleep = (unsigned int)ft_atoi_s(av[4]);
	(*config)->is_dead = FALSE;
	(*config)->is_completed = FALSE;
	if (ac == 6)
		(*config)->num_of_must_eat = ft_atoi_s(av[5]);
	if ((*config)->num_of_philos > MAX_NUM_THREADS)
		return (FALSE);
	(*config)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ((*config)->num_of_philos));
	if ((*config)->forks)
		(*config)->are_forks_taken = (t_bool *)malloc(sizeof(t_bool) * ((*config)->num_of_philos));
	if (!((*config)->forks) || !((*config)->are_forks_taken))
	{
		if ((*config)->forks)
		{
			free((*config)->forks);
			(*config)->forks = NULL;
		}
		free(*config);
		*config = NULL;
		return (FALSE);
	}
	memset((*config)->are_forks_taken, 0, sizeof(t_bool) * ((*config)->num_of_philos));
	i = 0;
	while (i < (*config)->num_of_philos)
	{
		ret = pthread_mutex_init(&((*config)->forks[i]), NULL);
		if (ret != 0)
			return (FALSE);
		i++;
	}
	ret = pthread_mutex_init(&((*config)->screen_lock), NULL);
	if (ret != 0)
		return (FALSE);
	ret = pthread_mutex_init(&((*config)->dead_lock), NULL);
	if (ret != 0)
		return (FALSE);
	return (TRUE);
}

t_philo
	*ft_create_philo(int i, t_config *conf)
{
	t_philo	*philo;
	int		ret;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ret = pthread_mutex_init(&(philo->meal_time_lock), NULL);
	if (ret != 0)
	{
		free(philo);
		philo = NULL;
		return (NULL);
	}
	philo->philo_id = i + 1;
	philo->last_meal_time = get_time();
	philo->config = conf;
	return (philo);
}

t_bool
	ft_monitor_philos(t_config *config, t_philo *philos)
{
	int			i;
	long		current_time;
	const int	num_of_philos = config->num_of_philos;
	const long	time_to_die = (long)config->time_to_die;

	i = 0;
	while(i < num_of_philos)
	{
		current_time = get_time();
		pthread_mutex_lock(&(config->screen_lock));
		if (current_time - philos[i].last_meal_time >= time_to_die)
		{
			config->is_dead = TRUE;
			print_msg(MESSAGE_TO_DIE, current_time, philos[i].philo_id);
			pthread_mutex_unlock(&(config->screen_lock));
			return (FALSE);
		}
		pthread_mutex_unlock(&(config->screen_lock));
		i++;
	}
	return (TRUE);
}

int
	main(int ac, char **av)
{
	int				ret;
	pthread_t		*ths;
	t_config		*config;
	t_philo			*philos;
	int				i;

	if (ac <= 4 || 7 <= ac || !ft_init_config(&config, ac, av))
		return (EXIT_FAILURE);
	ths = (pthread_t *)malloc(sizeof(pthread_t) * config->num_of_philos);
	philos = (t_philo *)malloc(sizeof(t_philo) * config->num_of_philos);
	if (!ths || !philos)
	{
		free(config);
		config = NULL;
		if (ths)
		{
			free(ths);
			ths = NULL;
		}
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < config->num_of_philos)
	{
		ret = pthread_mutex_init(&(philos[i].meal_time_lock), NULL);
		if (ret != 0)
		{
			// stop threads currently running
			free(philos);
			philos = NULL;
			free(config);
			config = NULL;
			return (EXIT_FAILURE);
		}
		philos[i].philo_id = i + 1;
		philos[i].last_meal_time = get_time();
		philos[i].config = config;
		ret = pthread_create(&ths[i], NULL, loop_philo, &philos[i]);
		if (ret != 0)
		{
			// stop threads currently running
			free(philos);
			philos = NULL;
			free(config);
			config = NULL;
			return (EXIT_FAILURE);
		}
		i++;
	}
	while (1)
	{
		if (!ft_monitor_philos(config, philos))
			break;
		usleep(MONITORING_INTERVAL);
	}
	i = 0;
	while (i < config->num_of_philos)
	{
		pthread_join(ths[i], NULL);
		i++;
	}
	free(ths);
	ths = NULL;
	i = 0;
	while (i < config->num_of_philos)
	{
		pthread_mutex_destroy(&(config->forks[i]));
		pthread_mutex_destroy(&(philos[i].meal_time_lock));
		i++;
	}
	free(config->forks);
	config->forks = NULL;
	free(config->are_forks_taken);
	config->are_forks_taken = NULL;
	free(philos);
	philos = NULL;
	pthread_mutex_destroy(&(config->screen_lock));
	pthread_mutex_destroy(&(config->dead_lock));
	free(config);
	config = NULL;
	return (EXIT_SUCCESS);
}
