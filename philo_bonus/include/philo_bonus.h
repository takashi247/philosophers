/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:16:37 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/27 13:44:40 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define MAX_NUM_THREADS 300
# define THOUSAND 1000
# define MONITORING_INTERVAL_IN_MS 9
# define INITIAL_USLEEP_VALUE 1000
# define NO_NUM_OF_MUST_EAT -1
# define CHILD_PROCESS 0
# define MESSAGE_TO_TAKE_A_FORK "has taken a fork\n"
# define MESSAGE_TO_EAT "is eating\n"
# define MESSAGE_TO_SLEEP "is sleeping\n"
# define MESSAGE_TO_THINK "is thinking\n"
# define MESSAGE_TO_DIE "died\n"
# define ERROR_MESSAGE "Error\n"
# define SEM4FORKS "/forks"
# define SEM4END "/end"
# define SEM4SCREEN "/screen"
# define PTHREAD_ERR_MSG "Can't start simulation due to pthread_create error\n"

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
	pid_t			*philo_pids;
	sem_t			*forks;
	sem_t			*sem_end;
	sem_t			*sem_screen;
}	t_config;

typedef struct s_philo
{
	int			philo_id;
	long		last_meal_time;
	int			num_of_meals_completed;
	t_bool		is_end;
	t_config	*config;
}	t_philo;

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
t_philo	*ft_create_philos(t_config *config);

/* ft_monitor_philo.c */
int		ft_monitor_philo(t_philo *philo);
void	ft_end_simulation(t_philo *philo);

/* philo_bonus.c */
void	ft_clear_config(t_config **config);
void	ft_exit_with_error(void);

/* ft_print_log.c */
void	ft_print_log(t_philo *philo, char *msg);
t_bool	ft_print_msg(char *msg, long current_time, int philo_id);
void	ft_safe_free(char **str);

/* ft_loop_philo.c */
t_bool	ft_is_loop_end(t_philo *philo);
void	*ft_loop_philo(void *arg);

/* philo_actions.c */
void	ft_drop_forks(t_philo *philo);
void	ft_take_forks(t_philo *philo);
void	ft_eat_spaghetti(t_philo *philo);
void	ft_sleep_tight(t_philo *philo);
void	ft_think_deep(t_philo *philo);

/* philo_actions_util.c */
void	ft_take_a_fork(sem_t *forks);
void	ft_drop_a_fork(sem_t *forks);
void	ft_sleep_in_millisecond(unsigned int micro_sec);
long	ft_get_time(void);

/* ft_init_config.c */
t_bool	ft_init_config(t_config **config, int ac, char **av);
void	ft_clear_philo_locks(int num_of_locks, t_philo *philos);

/* start_n_kill_processes.c */
void	ft_kill_processes(int num_of_processes, t_config *config);
void	ft_start_processes(t_philo *philos, t_config *config);

/* init_n_clear_sems.c */
void	ft_clear_sems(t_config *config);
void	ft_init_sems(t_config **config);

/* ft_wait_processes.c */
void	ft_wait_processes(t_config *config);

#endif
