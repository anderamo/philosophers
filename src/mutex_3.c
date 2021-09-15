/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:54:03 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/15 13:54:41 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mute_lock_final_par(size_t i)
{
	if (g_philo.data[0].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[0]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[0].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[0]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (0);
	}
	if (g_philo.data[i - 1].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[i - 1]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[i - 1].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[i - 1]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (i - 1);
	}
	return (-1);
}

int	mute_lock_head_par(size_t i)
{
	if (g_philo.data[i + 1].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[i + 1]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[i + 1].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[i + 1]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (i + 1);
	}
	if (g_philo.data[g_philo.philo - 1].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[g_philo.philo - 1]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[g_philo.philo - 1].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[g_philo.philo - 1]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (g_philo.philo - 1);
	}
	return (-1);
}

int	mute_lock_middle_par(size_t i)
{
	if (g_philo.data[i + 1].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[i + 1]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[i + 1].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[i + 1]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (i + 1);
	}
	if (g_philo.data[i - 1].fork == 1 && g_philo.data[i].fork == 1)
	{
		pthread_mutex_unlock(&g_philo.mutex_eat[i - 1]);
		pthread_mutex_unlock(&g_philo.mutex_eat[i]);
		g_philo.data[i - 1].fork = 0;
		g_philo.data[i].fork = 0;
		pthread_mutex_lock(&g_philo.mutex_eat[i - 1]);
		pthread_mutex_lock(&g_philo.mutex_eat[i]);
		return (i - 1);
	}
	return (-1);
}
