/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:05:23 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 18:38:16 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	monitor_philosophers(t_philo *philo)
{
	sem_wait(philo->config->meal_check);
	if ((get_time_now() - philo->last_meal_time) > philo->config->die_time)
	{
		sem_wait(philo->config->output);
		printf("%lld ", get_time_now() - philo->config->simulation_start);
		printf("%d ", philo->philo_id + 1);
		printf("%s\n", "is dead");
		sem_post(philo->config->output);
		sem_post(philo->config->meal_check);
		return (-1);
	}
	sem_post(philo->config->meal_check);
	return (1);
}

int	philosopher_eat(t_philo *philo)
{
	ft_usleep(1);
	sem_wait(philo->config->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->config->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->config->meal_check);
	philo->last_meal_time = get_time_now();
	sem_post(philo->config->meal_check);
	print_status(philo, "is eating");
	wait_for_duration(philo, philo->config->eat_duration);
	philo->meals_count++;
	sem_post(philo->config->forks);
	sem_post(philo->config->forks);
	return (0);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->config->meal_check);
		if ((get_time_now() - philo->last_meal_time) > philo->config->die_time)
		{
			sem_wait(philo->config->output);
			printf("%lld ", get_time_now() - philo->config->simulation_start);
			printf("%d ", philo->philo_id + 1);
			printf("%s\n", "is dead");
			sem_post(philo->config->output);
			sem_post(philo->config->meal_check);
			exit(1);
		}
		if (philo->config->meals_required && philo->meals_count
			>= philo->config->meals_required)
		{
			sem_post(philo->config->meal_check);
			break ;
		}
		(sem_post(philo->config->meal_check), usleep(100));
	}
	return (NULL);
}

void	philosopher_routine(t_philo *philo)
{
	t_config	*config;
	pthread_t	thread;

	config = philo->config;
	philo->last_meal_time = get_time_now();
	pthread_create(&thread, NULL, check_death, philo);
	if (philo->philo_id % 2)
		ft_usleep(50);
	while (1)
	{
		philosopher_eat(philo);
		print_status(philo, "is sleeping");
		wait_for_duration(philo, config->sleep_duration);
		print_status(philo, "is thinking");
		if (config->meals_required && \
		philo->meals_count >= config->meals_required)
			(pthread_join(thread, NULL), exit(0));
	}
	pthread_join(thread, NULL);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Error: Invalid number of arguments\n"));
	init_config(&config, argv);
	if (config.forks == SEM_FAILED || config.meal_check == SEM_FAILED || \
		config.output == SEM_FAILED || config.start == SEM_FAILED)
		(printf("sem_open failed"), exit(EXIT_FAILURE));
	i = -1;
	config.simulation_start = get_time_now();
	while (++i < config.num_philos)
	{
		config.pids[i] = fork();
		if (config.pids[i] == -1)
			exit(EXIT_FAILURE);
		else if (config.pids[i] == 0)
		{
			config.philos.config = &config;
			config.philos.philo_id = i;
			config.philos.meals_count = 0;
			philosopher_routine(&config.philos);
		}
	}
	return (cleanup_simulation(&config), 0);
}
