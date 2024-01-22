/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:01:11 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 17:32:31 by npirard          ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_philo {
	t_timeval	last_sleep;
	t_timeval	last_meal;
	int			nbr_meals;
	pthread_t	*thread;
	bool		is_dead;
}				t_philo;

typedef struct s_settings {
	int			nbr_philo;
	int			time_to_die;
	int			meal_duration;
	int			sleep_duration;
	int			nbr_meal_to_end;
}				t_settings;

int		ft_strtoi(const char *str, int *dest);
int		parse_settings(t_settings *settings, char **args, int argc);

void	error(char *str);

int		philo_alloc(t_settings *settings, pthread_t **threads_ptr,
			t_philo **philos_ptr);
void	philo_free(pthread_t **threads_ptr, t_philo **philos_ptr);
int		philo_create(t_settings *settings, pthread_t *threads,
			t_philo *philos);

void	*philo_routine(void *data);
bool	philo_check_dead(t_settings *settings, t_philo *philos);

#endif
