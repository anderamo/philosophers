/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:34:55 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/14 11:49:24 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutex(void)
{
	size_t	i;

	i = 0;
	while (i < g_philo.philo)
	{
		g_philo.data[i].fork = 1;
		g_philo.data[i].eat_count = 0;
		pthread_mutex_init(&g_philo.mutex_eat[i], NULL);
		i++;
	}
}

void	mutex_unlock_eat(int mute, size_t i)
{
	pthread_mutex_unlock(&g_philo.mutex_eat[mute]);
	g_philo.data[mute].fork = 1;
	g_philo.data[i].fork = 1;
}

void	destroy_mutex(void)
{
	size_t	i;

	i = 0;
	while (i < g_philo.philo)
	{
		pthread_mutex_destroy(&g_philo.mutex_eat[i]);
		i++;
	}
}
