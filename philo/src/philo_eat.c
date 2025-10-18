/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:28 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 16:33:49 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_config *config, t_philo *philo)
{
	if (philo->philo_id % 2 && config->num_philos % 2 == 0)
	{
		pthread_mutex_lock(&(config->forks[philo->right_fork_id]));
		print_status(config, philo->philo_id, "has taken a fork");
		if (config->num_philos == 1)
			return (pthread_mutex_unlock(&\
				(config->forks[philo->right_fork_id])), -1);
		pthread_mutex_lock(&(config->forks[philo->left_fork_id]));
		print_status(config, philo->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(config->forks[philo->left_fork_id]));
		print_status(config, philo->philo_id, "has taken a fork");
		if (config->num_philos == 1)
			return (pthread_mutex_unlock(&\
				(config->forks[philo->left_fork_id])), -1);
		pthread_mutex_lock(&(config->forks[philo->right_fork_id]));
		print_status(config, philo->philo_id, "has taken a fork");
	}
	return (0);
}

void	release_forks(t_config *config, t_philo *philo)
{
	if (philo->philo_id % 2 && config->num_philos % 2 == 0)
	{
		pthread_mutex_unlock(&(config->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(config->forks[philo->right_fork_id]));
	}
	else
	{
		pthread_mutex_unlock(&(config->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(config->forks[philo->left_fork_id]));
	}
}

int	philosopher_eat(t_config *config, t_philo *philo)
{
	if (take_forks(config, philo) == -1)
		return (-1);
	pthread_mutex_lock(&(config->meal_lock));
	philo->last_meal_time = get_time_now();
	philo->meals_count++;
	print_status(config, philo->philo_id, "is eating");
	pthread_mutex_unlock(&(config->meal_lock));
	wait_for_duration(config, config->eat_duration);
	release_forks(config, philo);
	return (0);
}
