/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:19:23 by tnishina          #+#    #+#             */
/*   Updated: 2021/11/27 00:32:57 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void
	printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
		(unsigned long)tid, (unsigned long)tid);
}

void
	*thr_fn(void *arg)
{
	(void)arg;
	printids("new thread: ");
	return ((void *)0);
}

int
	main(void)
{
	int			err;
	pthread_t	ntid;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		return (err);
	printids("main thread:");
	usleep(100);
	return (0);
}
