/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:01:11 by npirard           #+#    #+#             */
/*   Updated: 2024/01/23 18:08:49 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define NBR_PHILO 3
# define MEAL_DURATION 50
# define SLEEP_DURATION 100
# define TIME_TO_DIE 500
# define NBR_MEAL_TO_END 10

# define CL_0 "\033[0;30m"
# define CL_1 "\033[0;31m"
# define CL_2 "\033[0;32m"
# define CL_3 "\033[0;33m"
# define CL_4 "\033[0;34m"
# define CL_5 "\033[0;35m"
# define CL_6 "\033[0;36m"
# define CL_RS "\033[1;0m"

typedef enum e_msg_type
{
	msg_fork_taken,
	msg_is_eating,
	msg_is_sleeping,
	msg_is_thinking,
	msg_died,
	msg_created,
	msg_ended
}			t_msg_type;

typedef struct timeval	t_timeval;

typedef struct s_settings {
	int				nbr_philo;
	int				time_to_die;
	int				meal_duration;
	int				sleep_duration;
	int				nbr_meal_to_end;
	t_timeval		begin_time;
	pthread_mutex_t	count_mutex;
	pthread_mutex_t	begin_mutex;
	int				count;
	bool			begin;
}				t_settings;

typedef struct s_philo {
	int					number;
	t_timeval			last_sleep;
	t_timeval			last_meal;
	int					nbr_meals;
	pthread_t			thread;
	bool				is_dead;
	bool				has_left_fork;
	bool				has_right_fork;
	t_settings			*settings;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		local_mutex;
}						t_philo;

int		ft_strtoi(const char *str, int *dest);
int		parse_settings(t_settings *settings, char **args, int argc);

void	error(char *str);

int		philo_alloc(t_settings *settings, t_philo **philos_ptr);
int		fork_alloc(t_settings *settings, pthread_mutex_t **forks_ptr);
void	philo_free(t_settings *settings, t_philo **philos_ptr,
			pthread_mutex_t **forks_ptr);
int		philo_start(t_settings *settings, t_philo *philos,
			pthread_mutex_t *forks, pthread_mutex_t *print_mutex);
void	philo_print(int nbr_philo, t_philo *philos);
void	*philo_monitor(void *data);

void	print_settings(t_settings *settings);
int		print_msg(t_philo *philo, int action);

void	*philo_routine(void *data);
void	philo_die(t_philo *philo);
bool	philo_is_dead(t_philo *philo);
bool	check_time(t_timeval *last_time, int max);
int		take_both_forks(t_philo *philo);
int		unlock_forks(t_philo *philo);

#endif
