/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:59:05 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/14 20:04:00 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	size_t			eat_count;
	int				fork;
	struct timeval	end;
	struct timeval	start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		*tid;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	mutex_sleep;
	int				*a;
	size_t			eat_limit;
	long			t_sleep;
	long			t_die;
	long			t_eat;
	size_t			philo;
}	t_philo;

t_philo		g_philo;

int		ft_atoi_perf(char *str);
void	error_print(int error);
void	init_mutex(void);
int		mutex_lock_eat(size_t i);
void	mutex_unlock_eat(int mute, size_t i);
void	destroy_mutex(void);
void	*routine(void *eat);
void	check_alive(size_t i);

#endif
