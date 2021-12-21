/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/21 15:44:08 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define MAX_NUM_THREADS 300
# define THOUSAND 1000
# define MONITORING_INTERVAL 5
# define MESSAGE_TO_TAKE_FORK "%ld %d has taken a fork\n"
# define MESSAGE_TO_EAT "%ld %d is eating\n"
# define MESSAGE_TO_SLEEP "%ld %d is sleeping\n"
# define MESSAGE_TO_THINK "%ld %d is thinking\n"
# define MESSAGE_TO_DIE "%ld %d died\n"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_config
{
	int				num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				num_of_must_eat;
	t_bool			is_dead;
	pthread_mutex_t	screen_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
}	t_config;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	pthread_mutex_t	meal_time_lock;
	t_config		*config;
}	t_philo;

/* ft_isdigit.c */
int		ft_isdigit(int c);

/* ft_atoi_s.c */
int		ft_atoi_s(const char *str);

/* ft_isposint.c */
t_bool	ft_isposint(const char *str);

/* ft_strlen.c */
size_t	ft_strlen(const char *s);

/* ft_strncmp.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
