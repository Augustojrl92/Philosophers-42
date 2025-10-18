/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:29:01 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 17:52:27 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 - 48 + *str++;
	return (num * sign);
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

void	print_status(t_philo *philo, const char *status)
{
	sem_wait(philo->config->output);
	printf("%lld ", get_time_now() - philo->config->simulation_start);
	printf("%d ", philo->philo_id + 1);
	printf("%s\n", status);
	sem_post(philo->config->output);
	return ;
}
