/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isposint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 00:35:56 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/19 22:15:51 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool
	is_overflow(long l_num, char c)
{
	if (l_num > INT_MAX / 10
		|| (l_num == INT_MAX / 10 && c - '0' > INT_MAX % 10))
		return (TRUE);
	else
		return (FALSE);
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
	if (!*str || (*str == '0' && ft_isdigit(*(str + 1))))
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
