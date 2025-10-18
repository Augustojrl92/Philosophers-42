/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:22:49 by aurodrig          #+#    #+#             */
/*   Updated: 2024/11/17 14:05:00 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define SEM_FORKS "/sem_forks"
# define SEM_MEAL_CHECK "/sem_meal_check"
# define SEM_OUTPUT "/sem_output"
# define SEM_START "/sem_start"

typedef struct s_philo
{
	int				philo_id;
	int				meals_count;
	long long		last_meal_time;
	pid_t			pid;
	struct s_config	*config;
}				t_philo;

typedef struct s_config
{
	int				num_philos;
	int				die_time;
	int				eat_duration;
	int				sleep_duration;
	int				meals_required;
	int				simulation_end;
	long long		simulation_start;
	pid_t			*pids;
	t_philo			philos;
	sem_t			*forks;
	sem_t			*meal_check;
	sem_t			*output;
	sem_t			*start;
}				t_config;

long long	get_time_now(void);
void		print_status(t_philo *philo, const char *status);
int			init_semaphores(t_config *config);
int			init_config(t_config *config, char **argv);
void		cleanup_simulation(t_config *config);
void		philosopher_routine(t_philo *philo);
void		wait_for_duration(t_philo *philo, int time);
int			philosopher_eat(t_philo *philo);
int			monitor_philosophers(t_philo *philo);
void		ft_usleep(long long time);
void		*check_death(void *arg);
int			ft_nbr(char **argv);
int			ft_atoi(const char *str);

#endif
