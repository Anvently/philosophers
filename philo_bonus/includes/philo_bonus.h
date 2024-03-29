/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:01:11 by npirard           #+#    #+#             */
/*   Updated: 2024/02/01 18:05:15 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdbool.h>
# include <pthread.h>

# define NBR_PHILO 3
# define MEAL_DURATION 50
# define SLEEP_DURATION 100
# define TIME_TO_DIE 500
# define NBR_MEAL_TO_END 10

# define CL_0 "\001\033[0;30m\002"
# define CL_1 "\001\033[0;31m\002"
# define CL_2 "\001\033[0;32m\002"
# define CL_3 "\001\033[0;33m\002"
# define CL_4 "\001\033[0;34m\002"
# define CL_5 "\001\033[0;35m\002"
# define CL_6 "\001\033[0;36m\002"
# define CL_RS "\033[0m"

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
}				t_settings;

typedef struct s_philo {
	int					number;
	t_timeval			last_meal;
	t_timeval			begin_time;
	t_timeval			last_sleep;
	int					nbr_meals;
	bool				is_dead;
	t_settings			settings;
	char				*sem_local_name;
	char				*sem_tready_name;
	pid_t				*ids;
	sem_t				*sem_forks;
	sem_t				*sem_start;
	sem_t				*sem_pready;
	sem_t				*sem_tready;
	sem_t				*sem_print;
	sem_t				*sem_local;
	sem_t				*sem_eaten_enough;
}						t_philo;

int			ft_strtoi(const char *str, int *dest);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
int			parse_settings(t_settings *settings, char **args, int argc);

void		error(char *str);

void		print_settings(t_settings *settings);
int			print_msg(t_philo *philo, t_timeval *time, int action);

bool		check_time(t_timeval *time, t_timeval *last_time, int max);
void		usleep_calc(t_timeval *start_time, int duration);

int			philo_start(t_philo *philo);
void		philo_routine(t_philo *philo);
bool		philo_is_dead(t_philo *philo);
void		unlink_sem(char *local_name, char *tready_name);
int			init_sem(t_philo *philo);
int			init_monitor(t_philo *philo);
pthread_t	init_end_monitor(t_philo *philo);
void		kill_end_monitor(t_philo *philo);
void		free_philo(t_philo *philo);
void		free_exit(t_philo *philo, int status);
void		kill_all(pid_t *ids, t_philo *philo);

#endif
