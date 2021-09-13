/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:02:34 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/13 20:06:53 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	init_mutex()
{
	int i;

	i = 0;
	while(i < philo.philo)
	{
		philo.data[i].fork = 1;
		pthread_mutex_init(&philo.mutex_eat[i], NULL);
		i++;
	}
	//pthread_mutex_init(&philo->mutex_die, NULL);

	//pthread_mutex_init(&philo->mutex_sleep, NULL);
}

void	destroy_mutex()
{
	int i;

	i = 0;
	while(i < philo.philo)
	{
		pthread_mutex_destroy(&philo.mutex_eat[i]);
		i++;
	}
	//pthread_mutex_destroy(&philo->mutex_die);
	//pthread_mutex_destroy(&philo->mutex_sleep);
}
int mutex_lock_eat(int i)
{
	if (i == philo.philo - 1)
	{
		if (philo.data[i - 1].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[i - 1]);
			philo.data[i - 1].fork = 0;
			philo.data[i].fork = 0;
			return (i - 1);
		}
		if (philo.data[0].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[0]);
			philo.data[0].fork = 0;
			philo.data[i].fork = 0;
			return (0);
		}
	}
	else if (i == 0)
	{
		if (philo.data[i + 1].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[i + 1]);
			philo.data[i + 1].fork = 0;
			philo.data[i].fork = 0;
			return (i + 1);
		}
		if (philo.data[philo.philo - 1].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[philo.philo - 1]);
			philo.data[philo.philo - 1].fork = 0;
			philo.data[i].fork = 0;
			return (philo.philo - 1);
		}
	}
	else
	{
		if (philo.data[i + 1].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[i + 1]);
			philo.data[i + 1].fork = 0;
			philo.data[i].fork = 0;
			return (i + 1);
		}
		if (philo.data[i - 1].fork == 1 && philo.data[i].fork == 1)
		{
			pthread_mutex_lock(&philo.mutex_eat[i - 1]);
			philo.data[i - 1].fork = 0;
			philo.data[i].fork = 0;
			return (i - 1);
		}
	}
	return (-1);
}

void mutex_unlock_eat(int mute, int i)
{
	pthread_mutex_unlock(&philo.mutex_eat[mute]);
	philo.data[mute].fork = 1;
	philo.data[i].fork = 1;
}

void *eat(void *eat)
{
	int		i;
	int mute;

	i = *(int *)eat;
	mute = -1;
	while (mute == -1)
		mute = mutex_lock_eat(i);
	pthread_mutex_lock(&philo.mutex_eat[i]);
	gettimeofday(&philo.data->start, NULL);
	printf("%ld Philo %d has taken a fork\n", philo.data->start.tv_sec * 1000000 + philo.data->start.tv_usec, i);
	printf("%ld Philo %d is eating\n", philo.data->start.tv_sec * 1000000 + philo.data->start.tv_usec, i);
	usleep(philo.t_eat);
	gettimeofday(&philo.data->end, NULL);
	free(eat);
	pthread_mutex_unlock(&philo.mutex_eat[i]);
	mutex_unlock_eat(mute, i);
	return (NULL);
}

void philosophers(void)
{
	int	i;

	philo.mutex_eat = (pthread_mutex_t *)malloc(philo.philo * sizeof(pthread_mutex_t));
	philo.tid = (pthread_t *)malloc(philo .philo * sizeof(pthread_t));
	philo.data = (t_data *)malloc(philo.philo * sizeof(t_data));
	init_mutex();
	while (1)
	{
	i = 0;
	while(i < philo.philo)
	{
		philo.a = malloc(sizeof(int));
		*philo.a = i;
		pthread_create(&philo.tid[i], NULL, eat, philo.a);
		i++;
	}
	i = 0;
	while(i < philo.philo)
	{
		pthread_join(philo.tid[i], NULL);
		i++;
	}
	}
	destroy_mutex();
}

int	main(int a, char **argv)
{
	if (a >= 5 && a < 7)
	{
		philo.philo = ft_atoi_perf(argv[1]);
		philo.t_die = ft_atoi_perf(argv[2]);
		philo.t_eat = ft_atoi_perf(argv[3]);
		philo.t_sleep = ft_atoi_perf(argv[4]);
		if (a == 6)
			philo.eat_limit = ft_atoi_perf(argv[5]);
		philosophers();
	}
	else
		error_print(0);
	return (0);
}
