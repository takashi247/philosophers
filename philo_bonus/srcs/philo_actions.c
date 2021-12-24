/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:43:01 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_drop_forks(t_fork *right_fork, t_fork *left_fork)
{
	ft_drop_a_fork(right_fork);
	ft_drop_a_fork(left_fork);
}

void
	ft_take_forks(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	ft_take_a_fork(right_fork);
	ft_print_log(philo, MESSAGE_TO_TAKE_A_FORK);
	ft_take_a_fork(left_fork);
	ft_print_log(philo, MESSAGE_TO_TAKE_A_FORK);
}

void
	ft_eat_spaghetti(t_philo *philo)
{
	ft_print_log(philo, MESSAGE_TO_EAT);
	ft_sleep_in_millisecond(philo->config->time_to_eat);
}

void
	ft_sleep_tight(t_philo *philo)
{
	ft_print_log(philo, MESSAGE_TO_SLEEP);
	ft_sleep_in_millisecond(philo->config->time_to_sleep);
}

void
	ft_think_deep(t_philo *philo)
{
	ft_print_log(philo, MESSAGE_TO_THINK);
}
