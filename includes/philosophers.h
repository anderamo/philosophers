/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:59:05 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/07 15:11:13 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../ft_printf/includes/ft_printf.h"
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
	size_t	t_die;
	size_t	t_eat;
	size_t	eat_count;
	size_t	t_sleep;
	size_t	philo;
	struct timeval end;
	struct timeval start;
}	t_data;

typedef struct s_philo
{
	t_data			data;
	pthread_t		*tid;
	size_t			philo_index;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_sleep;
}	t_philo;


int		ft_atoi_perf(char *str);
void	error_print(int error);

#endif