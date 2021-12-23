/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 01:16:36 by tnishina         ###   ########.fr       */
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
	drop_a_fork(t_fork *fork)
{
	*(fork->is_taken) = FALSE;
	pthread_mutex_unlock(fork->fork_lock);
}

void
	ft_drop_forks(t_fork *right_fork, t_fork *left_fork)
{
	drop_a_fork(right_fork);
	drop_a_fork(left_fork);
}

void
	sleep_in_millisecond(unsigned int micro_sec)
{
	const long		start_time = get_time();
	const long		time_to_sleep = (long)micro_sec;
	unsigned int	usleep_time;

	while (get_time() - start_time < time_to_sleep)
	{
		usleep_time = INITIAL_USLEEP_VALUE;
		usleep_time /= 2;
		usleep(usleep_time);
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
		if (!ft_strncmp(msg, MESSAGE_TO_SLEEP, ft_strlen(MESSAGE_TO_SLEEP)))
		{
			philo->num_of_meals_completed++;
			if (philo->config->num_of_must_eat != NO_NUM_OF_MUST_EAT
				&& philo->num_of_meals_completed == philo->config->num_of_must_eat)
				*(philo->is_meal_completed) = TRUE;
		}
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
	ft_is_loop_end(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&(philo->config->screen_lock));
	res = philo->config->is_dead || philo->config->is_completed;
	pthread_mutex_unlock(&(philo->config->screen_lock));
	return (res);
}

void
	find_forks(t_fork *right_fork, t_fork *left_fork, const t_philo *philo)
{
	right_fork->fork_lock = &(philo->config->forks[philo->philo_id - 1]);
	right_fork->is_taken = &(philo->config->are_forks_taken[philo->philo_id - 1]);
	if (philo->philo_id < philo->config->num_of_philos)
	{
		left_fork->fork_lock = &(philo->config->forks[philo->philo_id]);
		left_fork->is_taken = &(philo->config->are_forks_taken[philo->philo_id]);
	}
	else
	{
		left_fork->fork_lock = &(philo->config->forks[0]);
		left_fork->is_taken = &(philo->config->are_forks_taken[0]);
	}
}

void
	*ft_loop_philo(void *arg)
{
	t_philo	*philo;
	t_fork	right_fork;
	t_fork	left_fork;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(200);
	find_forks(&right_fork, &left_fork, philo);
	if (philo->config->num_of_philos == 1)
	{
		take_a_fork(&right_fork);
		print_log(philo, MESSAGE_TO_TAKE_A_FORK);
		drop_a_fork(&right_fork);
		return ((void *)EXIT_SUCCESS);
	}
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

void
	ft_destroy_forks(t_config *config, int num_of_forks)
{
	int i;

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

t_bool
	ft_init_config(t_config **config, int ac, char **av)
{
	int	i;

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
	else
		(*config)->num_of_must_eat = NO_NUM_OF_MUST_EAT;
	if ((*config)->num_of_philos > MAX_NUM_THREADS)
		return (FALSE);
	(*config)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ((*config)->num_of_philos));
	(*config)->are_forks_taken = (t_bool *)malloc(sizeof(t_bool) * ((*config)->num_of_philos));
	(*config)->are_meals_completed = (t_bool *)malloc(sizeof(t_bool) * ((*config)->num_of_philos));
	if (!((*config)->forks) || !((*config)->are_forks_taken) || !((*config)->are_meals_completed))
	{
		ft_clear_config(config);
		return (FALSE);
	}
	memset((*config)->are_forks_taken, 0, sizeof(t_bool) * ((*config)->num_of_philos));
	memset((*config)->are_meals_completed, 0, sizeof(t_bool) * ((*config)->num_of_philos));
	i = 0;
	while (i < (*config)->num_of_philos)
	{
		if (pthread_mutex_init(&((*config)->forks[i]), NULL))
		{
			ft_destroy_forks(*config, i);
			return (FALSE);
		}
		i++;
	}
	if (pthread_mutex_init(&((*config)->screen_lock), NULL))
		return (FALSE);
	return (TRUE);
}

t_bool
	check_meals_completed(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_of_philos)
	{
		if (!philo->config->are_meals_completed[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void
	*ft_monitor_philo(void *arg)
{
	t_philo		*philo;
	t_config	*config;
	long		current_time;
	long		time_to_die;

	philo = (t_philo *)arg;
	config = philo->config;
	time_to_die = (long)philo->config->time_to_die;
	while(!ft_is_loop_end(philo))
	{
		usleep(MONITORING_INTERVAL);
		pthread_mutex_lock(&(config->screen_lock));
		current_time = get_time();
		if (current_time - philo->last_meal_time >= time_to_die)
		{
			config->is_dead = TRUE;
			print_msg(MESSAGE_TO_DIE, current_time, philo->philo_id);
		}
		if (check_meals_completed(philo))
			config->is_completed = TRUE;
		pthread_mutex_unlock(&(config->screen_lock));
	}
	return ((void *)EXIT_SUCCESS);
}

t_philo
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
		philos[i].last_meal_time = get_time();
		philos[i].num_of_meals_completed = 0;
		philos[i].is_meal_completed = &(config->are_meals_completed[i]);
		philos[i].config = config;
		i++;
	}
	return (philos);
}

t_bool
	ft_init_philos(pthread_t **ths_philo, pthread_t **ths_dr, t_philo **philos, t_config **config)
{
	*ths_philo = (pthread_t *)malloc(sizeof(pthread_t) * (*config)->num_of_philos);
	*ths_dr = (pthread_t *)malloc(sizeof(pthread_t) * (*config)->num_of_philos);
	*philos = create_philos(*config);
	if (!(*ths_philo) || !(*ths_dr) || !(*philos))
	{
		if (*ths_philo)
		{
			free(*ths_philo);
			*ths_philo = NULL;
		}
		if (*ths_dr)
		{
			free(*ths_philo);
			*ths_philo = NULL;
		}
		if (*philos)
		{
			free(*philos);
			*philos = NULL;
		}
		ft_clear_config(config);
		return (FALSE);
	}
	return (TRUE);
}

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
	ft_start_threads(pthread_t *ths_philo, pthread_t *ths_dr, t_philo *philos, t_config *config)
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

void
	ft_clean_up_all(pthread_t **ths_philo, pthread_t **ths_dr, t_philo **philos, t_config **config)
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

int
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
	ft_clean_up_all(&ths_philo, &ths_dr, &philos, &config);
	return (EXIT_SUCCESS);
}
