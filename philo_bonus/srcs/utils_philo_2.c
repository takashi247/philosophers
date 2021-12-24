/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:01:11 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int
	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;
	size_t			i;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (u_s1[i] || u_s2[i]))
	{
		if (u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	return (0);
}

void
	ft_putstr_fd(char *s, int fd)
{
	size_t	len_s;

	if (s && 0 <= fd)
	{
		len_s = ft_strlen(s);
		write(fd, s, len_s);
	}
}

void
	ft_putchar_fd(char c, int fd)
{
	if (0 <= fd)
		write(fd, &c, 1);
}

void
	ft_putendl_fd(char *s, int fd)
{
	if (s && 0 <= fd)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
