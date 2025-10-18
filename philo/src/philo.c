/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:33:51 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 16:25:56 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher_routine(void *v_philo)
{
	t_philo		*philo;
	t_config	*config;

	philo = (t_philo *)v_philo;
	config = philo->config;
	pthread_mutex_lock(&(config->init_philos));
	pthread_mutex_unlock(&(config->init_philos));
	if (philo->philo_id % 2)
		ft_usleep(50);
	pthread_mutex_lock(&(config->death_lock));
	while (!(config->simulation_end))
	{
		pthread_mutex_unlock(&(config->death_lock));
		if (philosopher_eat(config, philo) == -1)
			break ;
		print_status(config, philo->philo_id, "is sleeping");
		wait_for_duration(config, config->sleep_duration);
		print_status(config, philo->philo_id, "is thinking");
		if (config->meals_required != 0
			&& philo->meals_count >= config->meals_required)
			break ;
		pthread_mutex_lock(&(config->death_lock));
	}
	pthread_mutex_unlock(&(config->death_lock));
	return (NULL);
}

int	check_philosophers(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos && !(config->simulation_end))
	{
		pthread_mutex_lock(&(config->meal_lock));
		if ((get_time_now() - (config->philos[i].last_meal_time))
			>= config->die_time)
		{
			pthread_mutex_lock(&(config->print_lock));
			printf("%lld ", get_time_now() - config->simulation_start);
			printf("%d ", config->philos[i].philo_id + 1);
			printf("%s\n", "is dead");
			pthread_mutex_lock(&(config->death_lock));
			config->simulation_end = 1;
			pthread_mutex_unlock(&(config->meal_lock));
			pthread_mutex_unlock(&(config->print_lock));
			pthread_mutex_unlock(&(config->death_lock));
			return (-1);
		}
		pthread_mutex_unlock(&(config->meal_lock));
	}
	return (0);
}

void	monitor_philos(t_config *config)
{
	int	i;

	while (1)
	{
		if (check_philosophers(config) == -1)
			return ;
		i = 0;
		while (config->meals_required != 0 && i < config->num_philos && \
		config->philos[i].meals_count >= config->meals_required)
			i++;
		if (i == config->num_philos)
		{
			pthread_mutex_lock(&(config->death_lock));
			config->simulation_end = 1;
			pthread_mutex_unlock(&(config->death_lock));
			break ;
		}
		if (config->simulation_end)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			i;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_config(&config, argv) == -1)
		return (0);
	i = -1;
	pthread_mutex_lock(&(config.init_philos));
	while (++i < config.num_philos)
	{
		init_philo(&config, i);
		pthread_create(&(config.philos[i].thread), NULL,
			philosopher_routine, &(config.philos[i]));
	}
	config.simulation_start = get_time_now();
	pthread_mutex_unlock(&(config.init_philos));
	monitor_philos(&config);
	cleanup_simulation(&config);
	return (0);
}
