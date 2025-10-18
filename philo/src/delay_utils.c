/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:11:15 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 16:08:55 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time_now(void)
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
		usleep(9);
}

void	wait_for_duration(t_config *config, int duration)
{
	long long	start_time;

	start_time = get_time_now();
	while (1)
	{
		pthread_mutex_lock(&(config->death_lock));
		if (config->simulation_end)
		{
			pthread_mutex_unlock(&(config->death_lock));
			return ;
		}
		pthread_mutex_unlock(&(config->death_lock));
		if ((get_time_now() - start_time) >= duration)
			break ;
		usleep(100);
	}
}
