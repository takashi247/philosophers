/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:06:06 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool
	is_overflow(long l_num, char c)
{
	if (l_num > INT_MAX / 10
		|| (l_num == INT_MAX / 10 && c - '0' > INT_MAX % 10)
		|| l_num < INT_MIN / 10
		|| (l_num == INT_MIN / 10 && c - '0' > INT_MIN % 10 * -1))
		return (TRUE);
	else
		return (FALSE);
}

size_t
	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int
	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

/*
** return true if a number given as string is a valid positive integer
** within int range
*/

t_bool
	ft_isposint(const char *str)
{
	long	l_num;

	l_num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (FALSE);
		str++;
	}
	if (!*str || *str == '0')
		return (FALSE);
	while (ft_isdigit(*str))
	{
		if (is_overflow(l_num, *str))
			return (FALSE);
		l_num = l_num * 10 + (*str++ - '0');
	}
	if (*str)
		return (FALSE);
	return (TRUE);
}

/*
** return 0 if number is larger than INT_MAX or smaller than INT_MIN
*/

int
	ft_atoi_s(const char *str)
{
	long	l_num;
	int		sign;

	l_num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (is_overflow(sign * l_num, *str))
			return (0);
		l_num = l_num * 10 + (*str++ - '0');
	}
	return ((int)(sign * l_num));
}
