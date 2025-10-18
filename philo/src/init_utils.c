/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:21:08 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/12 21:35:08 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutexes(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_philos)
		pthread_mutex_init(&config->forks[i++], NULL);
	if (pthread_mutex_init(&(config->meal_lock), NULL) == -1 || \
		pthread_mutex_init(&(config->print_lock), NULL) == -1 || \
		pthread_mutex_init(&(config->death_lock), NULL) == -1 || \
		pthread_mutex_init(&(config->init_philos), NULL) == -1)
		return (printf("Error initializing mutexes\n"), (-1));
	return (0);
}

int	init_config(t_config *config, char **argv)
{
	if (ft_nbr(argv))
		(printf("Invalid argument\n"), exit(0));
	config->die_time = ((config->num_philos = ft_atoi(argv[1])), \
	ft_atoi(argv[2]));
	config->sleep_duration = ((config->eat_duration = ft_atoi(argv[3])), \
	ft_atoi(argv[4]));
	if (config->num_philos <= 0 || config->num_philos > 200 || \
	config->die_time < 60 || config->sleep_duration < 60 || \
	config->eat_duration < 60)
		return (printf("Invalid argument\n"), (-1));
	if (argv[5])
	{
		config->meals_required = ft_atoi(argv[5]);
		if (config->meals_required <= 0)
			return (printf("Invalid argument\n"), (-1));
	}
	else
		config->meals_required = 0;
	config->simulation_end = (0);
	config->forks = malloc((config->num_philos + 1) * sizeof(pthread_mutex_t));
	config->philos = (t_philo *)malloc((config->num_philos + 1) * \
	sizeof(t_philo));
	if (init_mutexes(config) == -1)
		return (-1);
	return (0);
}

void	init_philo(t_config *config, int index)
{
	config->philos[index].philo_id = index;
	config->philos[index].config = config;
	config->philos[index].meals_count = 0;
	config->philos[index].left_fork_id = index;
	config->philos[index].right_fork_id = (index + 1) % config->num_philos;
	config->philos[index].last_meal_time = get_time_now();
}

void	cleanup_simulation(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
		pthread_join(config->philos[i].thread, NULL);
	i = -1;
	while (++i < config->num_philos)
		pthread_mutex_destroy(&config->forks[i]);
	pthread_mutex_destroy(&(config->print_lock));
	pthread_mutex_destroy(&(config->meal_lock));
	pthread_mutex_destroy(&(config->death_lock));
	pthread_mutex_destroy(&(config->init_philos));
	free(config->forks);
	free(config->philos);
}
