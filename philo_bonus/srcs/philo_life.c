/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:35 by npirard           #+#    #+#             */
/*   Updated: 2024/02/02 10:39:42 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <stdio.h>

static int	take_fork(t_philo *philo)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	if (print_msg(philo, &time, msg_fork_taken))
		return (1);
	return (0);
}

static int	take_forks(t_philo *philo)
{
	t_timeval	time;

	while (1)
	{
		gettimeofday(&time, NULL);
		if (check_time(&time, &philo->last_sleep, 1) == false)
			usleep(1000);
		break ;
	}
	if (philo->settings.nbr_philo == 1)
	{
		take_fork(philo);
		usleep(philo->settings.time_to_die * 1000);
		return (1);
	}
	if (sem_wait(philo->sem_forks))
		return (1);
	if (philo_is_dead(philo))
		return (1);
	if (take_fork(philo))
		return (1);
	if (take_fork(philo))
		return (1);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	if (print_msg(philo, &time, msg_is_sleeping))
		return (1);
	usleep_calc(&time, philo->settings.sleep_duration);
	gettimeofday(&philo->last_sleep, NULL);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	t_timeval	time;

	if (take_forks(philo))
		return (1);
	if (philo_is_dead(philo))
		return (1);
	gettimeofday(&time, NULL);
	if (print_msg(philo, &time, msg_is_eating) || sem_wait(philo->sem_local))
		return (1);
	philo->last_meal = time;
	if (sem_post(philo->sem_local))
		return (1);
	usleep_calc(&time, philo->settings.meal_duration);
	if (sem_post(philo->sem_forks))
		return (1);
	if (philo->settings.nbr_meal_to_end >= 0
		&& ++philo->nbr_meals == philo->settings.nbr_meal_to_end)
	{
		gettimeofday(&time, NULL);
		if (print_msg(philo, &time, msg_ended)
			|| sem_post(philo->sem_eaten_enough))
			return (1);
	}
	return (0);
}

void	philo_routine(t_philo *philo)
{
	t_timeval	time;

	if (init_monitor(philo))
		free_exit(philo, 1);
	if (sem_post(philo->sem_pready))
		free_exit(philo, 1);
	if (sem_wait(philo->sem_start))
		free_exit(philo, 1);
	if (sem_wait(philo->sem_local))
		free_exit(philo, 1);
	gettimeofday(&philo->begin_time, NULL);
	if (sem_post(philo->sem_local))
		free_exit(philo, 1);
	while (1)
	{
		if (philo_is_dead(philo) || philo_eat(philo))
			free_exit(philo, 1);
		if (philo_is_dead(philo) || philo_sleep(philo))
			free_exit(philo, 1);
		gettimeofday(&time, NULL);
		if (philo_is_dead(philo) || print_msg(philo, &time, msg_is_thinking))
			free_exit(philo, 1);
	}
}
