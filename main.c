/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:02:34 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/15 14:07:50 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	check_all_eat(void)
{
	size_t	i;

	if (g_philo.eat_limit == 0)
		return (0);
	i = 0;
	while (i < g_philo.philo)
	{
		if (g_philo.data[i].eat_count != g_philo.eat_limit)
			return (0);
		i++;
	}
	return (1);
}

void	philosophers(void)
{
	size_t	i;

	g_philo.mutex_eat = (pthread_mutex_t *)malloc(g_philo.philo
			* sizeof(pthread_mutex_t));
	g_philo.tid = (pthread_t *)malloc(g_philo.philo * sizeof(pthread_t));
	g_philo.data = (t_data *)malloc(g_philo.philo * sizeof(t_data));
	init_mutex();
	while (!check_all_eat())
	{
		i = 0;
		while (i < g_philo.philo)
		{
			g_philo.a = malloc(sizeof(int));
			*g_philo.a = i;
			pthread_create(&g_philo.tid[i], NULL, routine, g_philo.a);
			i++;
		}
		i = 0;
		while (i < g_philo.philo)
		{
			pthread_join(g_philo.tid[i], NULL);
			i++;
			usleep(1000);
		}
	}
	destroy_mutex();
}

int	main(int a, char **argv)
{
	if (a >= 5 && a < 7)
	{
		g_philo.philo = ft_atoi_perf(argv[1]);
		g_philo.t_die = ft_atoi_perf(argv[2]);
		g_philo.t_eat = ft_atoi_perf(argv[3]);
		g_philo.t_sleep = ft_atoi_perf(argv[4]);
		if (a == 6)
		{
			g_philo.eat_limit = ft_atoi_perf(argv[5]);
			if (g_philo.eat_limit < 1)
				return (0);
		}
		else
			g_philo.eat_limit = 0;
		philosophers();
	}
	else
		error_print(0);
	return (0);
}
