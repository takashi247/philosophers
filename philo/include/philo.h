/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 14:21:15 by tnishina         ###   ########.fr       */
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
# define MONITORING_INTERVAL_IN_MS 9
# define INITIAL_USLEEP_VALUE 500
# define NO_NUM_OF_MUST_EAT -1
# define MESSAGE_TO_TAKE_A_FORK "has taken a fork\n"
# define MESSAGE_TO_EAT "is eating\n"
# define MESSAGE_TO_SLEEP "is sleeping\n"
# define MESSAGE_TO_THINK "is thinking\n"
# define MESSAGE_TO_DIE "died\n"
# define ERROR_MESSAGE "Error\n"

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
	pthread_mutex_t	*forks;
	t_bool			*are_forks_taken;
	t_bool			*are_meals_completed;
}	t_config;

typedef struct s_philo
{
	int			philo_id;
	long		last_meal_time;
	int			num_of_meals_completed;
	t_bool		*is_meal_completed;
	t_config	*config;
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

/* ft_init_philo.c */
t_bool	ft_init_philos(pthread_t **ths_philo, pthread_t **ths_dr, \
t_philo **philos, t_config **config);

/* ft_monitor_philo.c */
void	*ft_monitor_philo(void *arg);

/* philo.c */
void	ft_destroy_forks(t_config *config, int num_of_forks);
void	ft_clear_config(t_config **config);

/* ft_print_log.c */
void	ft_print_log(t_philo *philo, char *msg);
t_bool	ft_print_msg(char *msg, long current_time, int philo_id);

/* start_n_join_ths.c */
void	ft_join_threads(pthread_t *ths_philo, pthread_t *ths_dr, \
int num_of_ths);
t_bool	ft_start_threads(pthread_t *ths_philo, pthread_t *ths_dr, \
t_philo *philos, t_config *config);

/* ft_loop_philo.c */
t_bool	ft_is_loop_end(t_philo *philo);
void	*ft_loop_philo(void *arg);

/* philo_actions.c */
void	ft_drop_forks(t_fork *right_fork, t_fork *left_fork);
void	ft_take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork);
void	ft_eat_spaghetti(t_philo *philo);
void	ft_sleep_tight(t_philo *philo);
void	ft_think_deep(t_philo *philo);

/* philo_actions_util.c */
void	ft_take_a_fork(t_fork *fork);
void	ft_drop_a_fork(t_fork *fork);
void	ft_sleep_in_millisecond(unsigned int micro_sec);
long	ft_get_time(void);

/* ft_init_config.c */
t_bool	ft_init_config(t_config **config, int ac, char **av);

#endif
