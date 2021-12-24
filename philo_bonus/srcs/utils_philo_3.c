/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:14:03 by tnishina          #+#    #+#             */
/*   Updated: 2021/12/24 17:28:05 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t
	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	if (!src)
		return (0);
	len_src = ft_strlen(src);
	if (!dst || !dstsize)
		return (len_src);
	i = 0;
	while (i < len_src && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	if (!src || !dst)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	i = 0;
	while (src[i] && i < dstsize - len_dst - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}

char
	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*head;

	if (!s1)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	head = dup;
	while (*s1)
		*dup++ = *s1++;
	*dup = '\0';
	return (head);
}

char
	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_joined;
	char	*s_joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_joined = ft_strlen(s1) + ft_strlen(s2);
	s_joined = (char *)malloc(sizeof(char) * (len_joined + 1));
	if (!s_joined)
		return (NULL);
	ft_strlcpy(s_joined, s1, len_joined + 1);
	ft_strlcat(s_joined, s2, len_joined + 1);
	return (s_joined);
}
