/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 23:56:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/17 23:57:06 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	is_overflow(long l_num, char c)
{
	if (l_num > INT_MAX / 10
		|| (l_num == INT_MAX / 10 && c - '0' > INT_MAX % 10)
		|| l_num < INT_MIN / 10
		|| (l_num == INT_MIN / 10 && c - '0' > INT_MIN % 10 * -1))
		return (1);
	else
		return (0);
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
