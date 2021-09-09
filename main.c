/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:02:34 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/07 15:57:16 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

t_philo	*init_mutex(t_philo	*philo)
{
	pthread_mutex_init(&philo->mutex_die, NULL);
	pthread_mutex_init(&philo->mutex_eat, NULL);
	pthread_mutex_init(&philo->mutex_sleep, NULL);
	return (philo);
}

t_philo	*destroy_mutex(t_philo	*philo)
{
	pthread_mutex_destroy(&philo->mutex_die);
	pthread_mutex_destroy(&philo->mutex_eat);
	pthread_mutex_destroy(&philo->mutex_sleep);
	return (philo);
}

void *eat(void *eat)
{
	t_philo	*philo;
	int		i;

	i = (int)eat;
	printf("%d\n", philo->tid[i]);
	/*
	pthread_mutex_lock(&philo->mutex_eat);
	gettimeofday(&philo->data.start, NULL);
	printf("%ld Philo %zu is eating\n", philo->data.start.tv_sec * 1000000 + philo->data.start.tv_usec, philo->philo_index);
	usleep(philo->data.t_eat);
	gettimeofday(&philo->data.end, NULL);
	pthread_mutex_unlock(&philo->mutex_eat);
	*/
	return (NULL);
}

void philosophers(t_philo		*philo)
{
	size_t			i;

	philo = init_mutex(philo);
	philo->tid = (pthread_t *)malloc(philo->data.philo * sizeof(pthread_t));
	i = 0;
	while(i < philo->data.philo)
	{
		pthread_create(&philo->tid[i], NULL, eat, (void *)i);
		i++;
	}
	i = 0;
	while(i < philo->data.philo)
	{
		pthread_join(philo->tid[i], NULL);
		i++;
	}
	philo = destroy_mutex(philo);
}

int	main(int a, char **argv)
{
	t_philo		philo;

	if (a >= 5 && a < 7)
	{
		philo.data.philo = ft_atoi_perf(argv[1]);
		philo.data.t_die = ft_atoi_perf(argv[2]);
		philo.data.t_eat = ft_atoi_perf(argv[3]);
		philo.data.t_sleep = ft_atoi_perf(argv[4]);
		if (a == 6)
			philo.data.eat_count = ft_atoi_perf(argv[5]);
		philosophers(&philo);
	}
	else
		error_print(0);
	return (0);
}
