/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/22 18:22:19 by tnishina         ###   ########.fr       */
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
# include <string.h>

# define MAX_NUM_THREADS 300
# define THOUSAND 1000
# define MONITORING_INTERVAL 200
# define INITIAL_USLEEP_VALUE 1000
# define MESSAGE_TO_TAKE_A_FORK "has taken a fork\n"
# define MESSAGE_TO_EAT "is eating\n"
# define MESSAGE_TO_SLEEP "is sleeping\n"
# define MESSAGE_TO_THINK "is thinking\n"
# define MESSAGE_TO_DIE "died\n"

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
	t_bool			is_completed;
	pthread_mutex_t	screen_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_bool			*are_forks_taken;
}	t_config;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	pthread_mutex_t	meal_time_lock;
	int				num_of_meals_completed;
	t_config		*config;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	*fork_lock;
	t_bool			*is_taken;
}	t_fork;

/* utils_philo_1.c */
int		ft_isdigit(int c);
int		ft_atoi_s(const char *str);
t_bool	ft_isposint(const char *str);
size_t	ft_strlen(const char *s);

/* utils_philo_2.c */
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* utils_philo_3.c */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

/* ft_itoa.c */
char	*ft_itoa(int n);

/* ft_convert_time2str.c */
char	*ft_convert_time2str(long time);

#endif
