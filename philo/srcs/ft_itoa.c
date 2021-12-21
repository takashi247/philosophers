/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:17:31 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/21 22:17:52 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int
	check_intlen(int n)
{
	long	long_n;
	int		len_n;

	long_n = (long)n;
	if (long_n == 0)
		return (1);
	len_n = 0;
	if (long_n < 0)
	{
		len_n++;
		long_n *= -1;
	}
	while (long_n)
	{
		len_n++;
		long_n /= 10;
	}
	return (len_n);
}

static int
	compute_divider(int n, const int len_of_int)
{
	int	len_of_divider;
	int	divider;

	len_of_divider = len_of_int - (n < 0);
	divider = 1;
	while (len_of_divider != 1)
	{
		divider *= 10;
		len_of_divider--;
	}
	return (divider);
}

char
	*ft_itoa(int n)
{
	long		long_n;
	const int	len_of_int = check_intlen(n);
	char		*num_str;
	int			divider;
	char		*head;

	long_n = (long)n;
	num_str = (char *)malloc(sizeof(char) * (len_of_int + 1));
	if (!num_str)
		return (NULL);
	head = num_str;
	divider = compute_divider(n, len_of_int);
	if (n < 0)
	{
		*num_str++ = '-';
		long_n *= -1;
	}
	while (divider)
	{
		*num_str++ = long_n / divider + '0';
		long_n %= divider;
		divider /= 10;
	}
	*num_str = '\0';
	return (head);
}
