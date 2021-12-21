/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_time2str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:21:08 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/21 22:37:10 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	check_intlen(long time)
{
	long long	ll_time;
	int			len_n;

	ll_time = (long long)time;
	if (ll_time == 0)
		return (1);
	len_n = 0;
	while (ll_time)
	{
		len_n++;
		ll_time /= 10;
	}
	return (len_n);
}

static long long
	compute_divider(int len_of_int)
{
	long long	divider;

	divider = 1;
	while (len_of_int != 1)
	{
		divider *= 10;
		len_of_int--;
	}
	return (divider);
}

char
	*ft_convert_time2str(long time)
{
	long long	ll_time;
	const int	len_of_time = check_intlen(time);
	char		*num_str;
	long long	divider;
	char		*head;

	ll_time = (long long)time;
	num_str = (char *)malloc(sizeof(char) * (len_of_time + 1));
	if (!num_str)
		return (NULL);
	head = num_str;
	divider = compute_divider(len_of_time);
	while (divider)
	{
		*num_str++ = ll_time / divider + '0';
		ll_time %= divider;
		divider /= 10;
	}
	*num_str = '\0';
	return (head);
}
