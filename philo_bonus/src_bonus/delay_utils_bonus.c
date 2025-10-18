/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:45:53 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 18:44:12 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

long long	get_time_now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time_now();
	while (get_time_now() < start + time)
		usleep(10);
}

void	wait_for_duration(t_philo *philo, int time)
{
	long long	start_time;

	start_time = get_time_now();
	while (monitor_philosophers(philo))
	{
		if ((get_time_now() - start_time) >= time)
			break ;
		usleep(100);
	}
	return ;
}
