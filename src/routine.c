/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:36:31 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/14 20:33:03 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_eat_count(size_t i, int mute)
{
	if (g_philo.eat_limit != 0)
	{
		if (g_philo.data[i].eat_count >= g_philo.eat_limit)
		{
			printf("Philo %zu have reach ", i + 1);
			printf("the eaten limit = %zu\n", g_philo.eat_limit);
			mutex_unlock_eat(mute, i);
		}
	}
}

void	sleep_think_philo(size_t i)
{
	int	n;

	n = 1000;
	printf("%ld Philo %zu is spleeping\n", g_philo.data[i].start.tv_sec
		* n + g_philo.data[i].start.tv_usec, i + 1);
	usleep(g_philo.t_sleep * 1000);
	printf("%ld Philo %zu is thinking\n", g_philo.data[i].start.tv_sec
		* n + g_philo.data[i].start.tv_usec, i + 1);
}

void	eat_philo(size_t i, int mute)
{
	gettimeofday(&g_philo.data[i].end, NULL);
	printf("%ld Philo %zu has taken a fork\n", g_philo.data[i].end.tv_sec
		* 1000 + g_philo.data[i].end.tv_usec, i + 1);
	printf("%ld Philo %zu is eating\n", g_philo.data[i].end.tv_sec
		* 1000 + g_philo.data[i].end.tv_usec, i + 1);
	check_alive(i);
	check_eat_count(i, mute);
	usleep(g_philo.t_eat * 1000);
	gettimeofday(&g_philo.data[i].start, NULL);
}

void	check_alive(size_t i)
{
	int		n;

	n = 1000;
	gettimeofday(&g_philo.data[i].end, NULL);
	if ((g_philo.data[i].end.tv_sec * n + g_philo.data[i].end.tv_usec)
		- (g_philo.data[i].start.tv_sec * n + g_philo.data[i].start.tv_usec)
		> (g_philo.t_die * 1000))
	{
		printf("%ld Philo %zu die\n", (g_philo.data[i].end.tv_sec
			* 1000 + g_philo.data[i].end.tv_usec), i + 1);
		destroy_mutex();
		exit(1);
	}
}

void	*routine(void *eat)
{
	size_t		i;
	int			mute;

	i = *(int *)eat;
	if (g_philo.eat_limit != 0)
	{
		if (g_philo.data[i].eat_count >= g_philo.eat_limit)
			return (NULL);
	}
	mute = -1;
	gettimeofday(&g_philo.data[i].start, NULL);
	while (mute == -1)
	{
		check_alive(i);
		mute = mutex_lock_eat(i);
	}
	pthread_mutex_lock(&g_philo.mutex_eat[i]);
	g_philo.data[i].eat_count++;
	eat_philo(i, mute);
	free(eat);
	pthread_mutex_unlock(&g_philo.mutex_eat[i]);
	mutex_unlock_eat(mute, i);
	sleep_think_philo(i);
	check_alive(i);
	return (NULL);
}
