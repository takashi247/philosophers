/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:52:13 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/25 12:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
	safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

static char
	*create_msg(char *msg, char *str_time, char *str_id)
{
	char	*str_combined;
	char	*tmp;

	str_combined = ft_strjoin(str_time, " ");
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, str_id);
	safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, " ");
	safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	tmp = str_combined;
	str_combined = ft_strjoin(tmp, msg);
	safe_free(&tmp);
	if (!str_combined)
		return (NULL);
	return (str_combined);
}

t_bool
	ft_print_msg(char *msg, long current_time, int philo_id)
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
			safe_free(&str_time);
		res = FALSE;
		return (res);
	}
	str_combined = create_msg(msg, str_time, str_id);
	if (!str_combined)
		res = FALSE;
	else
		ft_putstr_fd(str_combined, STDOUT_FILENO);
	safe_free(&str_combined);
	safe_free(&str_time);
	safe_free(&str_id);
	return (res);
}

void
	ft_print_log(t_philo *philo, char *msg)
{
	t_bool	res;
	long	current_time;

	sem_wait(philo->waiter);
	if (!philo->config->is_dead && !philo->config->is_completed)
	{
		current_time = ft_get_time();
		res = ft_print_msg(msg, current_time, philo->philo_id);
		if (!res)
			philo->config->is_completed = TRUE;
		if (!ft_strncmp(msg, MESSAGE_TO_EAT, ft_strlen(MESSAGE_TO_EAT)))
			philo->last_meal_time = current_time;
		if (!ft_strncmp(msg, MESSAGE_TO_SLEEP, ft_strlen(MESSAGE_TO_SLEEP)))
		{
			philo->num_of_meals_completed++;
			if (philo->config->num_of_must_eat != NO_NUM_OF_MUST_EAT \
			&& philo->num_of_meals_completed == philo->config->num_of_must_eat)
				*(philo->is_meal_completed) = TRUE;
		}
	}
	sem_post(philo->waiter);
}
