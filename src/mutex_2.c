/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:49:26 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/15 17:26:08 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	mute_lock_final_impar(size_t i)
{
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
	return (-1);
}

int	mute_lock_head_impar(size_t i)
{
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
	return (-1);
}

int	mute_lock_middle_impar(size_t i)
{
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
	return (-1);
}

int	mutex_lock_eat(size_t i)
{
	int	mute;

	mute = -1;
	if (g_philo.philo == 1)
		return (mute);
	if (i % 2 == 0)
	{
		if (i == 0)
			mute = mute_lock_head_par(i);
		else if (i == g_philo.philo - 1)
			mute = mute_lock_final_par(i);
		else
			mute = mute_lock_middle_par(i);
	}
	else
	{
		if (i == 0)
			mute = mute_lock_head_impar(i);
		else if (i == g_philo.philo - 1)
			mute = mute_lock_final_impar(i);
		else
			mute = mute_lock_middle_impar(i);
	}
	return (mute);
}
