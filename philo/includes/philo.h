/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:53:34 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/07 11:45:29 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				philo_id;
	int				meals_count;
	long long		last_meal_time;
	pthread_t		thread;
	int				left_fork_id;
	int				right_fork_id;
	struct s_config	*config;
}			t_philo;

typedef struct s_config
{
	int				num_philos;
	int				die_time;
	int				eat_duration;
	int				sleep_duration;
	int				meals_required;
	int				simulation_end;
	long long		simulation_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	init_philos;
}			t_config;

int		ft_nbr(char **argv);
int		ft_atoi(const char *str);
void	ft_usleep(long long ms);
long	get_time_now(void);
int		init_mutexes(t_config *config);
int		init_config(t_config *config, char **argv);
void	init_philo(t_config *config, int index);
void	cleanup_simulation(t_config *config);
void	*philosopher_routine(void *v_philo);
void	print_status(t_config *config, int philo_id, const char *status);
void	wait_for_duration(t_config *config, int duration);
int		take_forks(t_config *config, t_philo *philo);
void	release_forks(t_config *config, t_philo *philo);
int		philosopher_eat(t_config *config, t_philo *philo);
void	monitor_philos(t_config *config);

#endif