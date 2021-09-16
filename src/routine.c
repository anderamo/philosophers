/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:36:31 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/16 10:44:09 by aamorin-         ###   ########.fr       */
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

int	eat_philo(size_t i, int mute)
{
	gettimeofday(&g_philo.data[i].end, NULL);
	printf("%ld Philo %zu has taken a fork\n", g_philo.data[i].end.tv_sec
		* 1000 + g_philo.data[i].end.tv_usec, i + 1);
	printf("%ld Philo %zu is eating\n", g_philo.data[i].end.tv_sec
		* 1000 + g_philo.data[i].end.tv_usec, i + 1);
	if (check_alive(i) == -2)
		return (-2);
	check_eat_count(i, mute);
	usleep(g_philo.t_eat * 1000);
	gettimeofday(&g_philo.data[i].start, NULL);
	mutex_unlock_eat(mute, i);
	sleep_think_philo(i);
	return (0);
}

int	check_alive(size_t i)
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
		return (-2);
	}
	return (-1);
}

void	*routine(void *eat)
{
	size_t		i;
	int			mute;

	i = *(int *)eat;
	free(eat);
	if (g_philo.eat_limit != 0)
	{
		if (g_philo.data[i].eat_count >= g_philo.eat_limit)
			return ((void *)-2);
	}
	mute = -1;
	gettimeofday(&g_philo.data[i].start, NULL);
	while (mute == -1)
	{
		mute = mutex_lock_eat(i);
		if (check_alive(i) == -2 || mute == -2)
			return ((void *)-2);
	}
	g_philo.data[i].eat_count++;
	mute = eat_philo(i, mute);
	return ((void *)0);
}
