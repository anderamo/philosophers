/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:36:31 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/14 12:32:36 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_eat_count(size_t i)
{
	if (g_philo.eat_limit != 0)
	{
		if (g_philo.data[i].eat_count >= g_philo.eat_limit)
		{
			printf("Philo %zu have reach ", i);
			printf("the eaten limit = %zu\n", g_philo.eat_limit);
			destroy_mutex();
			exit(1);
		}
	}
}

void	sleep_think_philo(size_t i)
{
	int	n;

	n = 1000000;
	printf("%ld Philo %zu is spleeping\n", g_philo.data[i].start.tv_sec
		* n + g_philo.data[i].start.tv_usec, i);
	usleep(g_philo.t_sleep);
	printf("%ld Philo %zu is thinking\n", g_philo.data[i].start.tv_sec
		* n + g_philo.data[i].start.tv_usec, i);
}

void	eat_philo(size_t i)
{
	printf("%ld Philo %zu has taken a fork\n", g_philo.data[i].start.tv_sec
		* 1000000 + g_philo.data[i].start.tv_usec, i);
	printf("%ld Philo %zu is eating\n", g_philo.data[i].start.tv_sec
		* 1000000 + g_philo.data[i].start.tv_usec, i);
	check_eat_count(i);
	usleep(g_philo.t_eat);
}

void	check_alive(size_t i)
{
	int	n;

	n = 1000000;
	gettimeofday(&g_philo.data[i].end, NULL);
	if ((g_philo.data[i].end.tv_sec * n + g_philo.data[i].end.tv_usec)
		- (g_philo.data[i].start.tv_sec * n + g_philo.data[i].start.tv_usec)
		> g_philo.t_die)
	{
		printf("%ld Philo %zu die\n", g_philo.data[i].end.tv_sec
			* n + g_philo.data[i].end.tv_usec, i);
		destroy_mutex();
		exit(1);
	}
}

void	*routine(void *eat)
{
	size_t		i;
	int			mute;

	i = *(int *)eat;
	mute = -1;
	gettimeofday(&g_philo.data[i].start, NULL);
	while (mute == -1)
	{
		check_alive(i);
		mute = mutex_lock_eat(i);
	}
	pthread_mutex_lock(&g_philo.mutex_eat[i]);
	g_philo.data[i].eat_count++;
	eat_philo(i);
	gettimeofday(&g_philo.data[i].start, NULL);
	free(eat);
	pthread_mutex_unlock(&g_philo.mutex_eat[i]);
	mutex_unlock_eat(mute, i);
	sleep_think_philo(i);
	check_alive(i);
	return (NULL);
}
