/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:05:27 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/07 11:49:18 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_nbr(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
		}
		i++;
	}
	return (0);
}

void	print_status(t_config *config, int philo_id, const char *status)
{
	pthread_mutex_lock(&(config->print_lock));
	pthread_mutex_lock(&(config->death_lock));
	if (!(config->simulation_end))
	{
		pthread_mutex_unlock(&(config->death_lock));
		printf("%lld ", get_time_now() - config->simulation_start);
		printf("%d ", philo_id + 1);
		printf("%s\n", status);
	}
	else
		pthread_mutex_unlock(&(config->death_lock));
	pthread_mutex_unlock(&(config->print_lock));
	return ;
}
