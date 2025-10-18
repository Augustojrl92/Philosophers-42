/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:27:27 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/15 18:43:56 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	init_semaphores(t_config *config)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MEAL_CHECK);
	sem_unlink(SEM_OUTPUT);
	config->forks = sem_open(SEM_FORKS, O_CREAT, 0644, config->num_philos);
	config->meal_check = sem_open(SEM_MEAL_CHECK, O_CREAT, 0644, 1);
	config->output = sem_open(SEM_OUTPUT, O_CREAT, 0644, 1);
	config->pids = (pid_t *)malloc(sizeof(pid_t) * config->num_philos + 1);
	if (config->forks == SEM_FAILED || config->meal_check == SEM_FAILED
		||config->output == SEM_FAILED || config->start == SEM_FAILED)
	{
		printf("Error initializing semaforos\n");
		return (-1);
	}
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
	if (config->num_philos < 1 || config->die_time < 60 || \
		config->eat_duration < 60 || config->sleep_duration < 60)
		(printf("Invalid argument\n"), exit(0));
	if (argv[5])
	{
		config->meals_required = ft_atoi(argv[5]);
		if (config->meals_required <= 0)
			(printf("Invalid argument\n"), exit(0));
	}
	else
		config->meals_required = 0;
	if (init_semaphores(config) == -1)
		return (-1);
	return (0);
}

void	cleanup_simulation(t_config *config)
{
	int	i;
	int	status;

	i = -1;
	while (++i < config->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < config->num_philos)
				kill(config->pids[i], 15);
			break ;
		}
	}
	sem_close(config->meal_check);
	sem_close(config->output);
	sem_close(config->forks);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MEAL_CHECK);
	sem_unlink(SEM_OUTPUT);
	free(config->pids);
}
