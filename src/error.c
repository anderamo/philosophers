/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:42:32 by aamorin-          #+#    #+#             */
/*   Updated: 2021/09/14 12:18:58 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	error_print(int error)
{
	if (error == 0)
	{
		printf("ERROR 0. The amount of parameters must be between 5 or 6, exa");
		printf("mple :\n./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_should_eat]\n");
	}
	if (error == 1)
	{
		printf("ERROR 1. The parameters are not numbers, example :\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_should_eat]\n");
	}
	exit(0);
}
