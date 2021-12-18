/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/18 17:04:31 by tnishina         ###   ########.fr       */
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

# define MAX_NUM_THREADS 500

typedef struct s_config
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	forks[MAX_NUM_THREADS / 2];
}	t_config;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo
{
	int			philo_id;
	t_config	*config;
}	t_philo;

/* ft_isdigit.c */
int		ft_isdigit(int c);

/* ft_atoi_s.c */
int		ft_atoi_s(const char *str);

/* ft_isint.c */
t_bool	ft_isint(const char *str);

#endif
