/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:35 by npirard           #+#    #+#             */
/*   Updated: 2024/01/25 18:56:14 by npirard          ###   ########.fr       */
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
	if (sem_wait(philo->sem_forks))
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
	usleep(1000 * philo->settings.sleep_duration);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	t_timeval	time;

	if (take_forks(philo))
		return (1);
	gettimeofday(&time, NULL);
	if (print_msg(philo, &time, msg_is_eating) || sem_wait(philo->sem_local))
		return (1);
	philo->last_meal = time;
	if (sem_post(philo->sem_local))
		return (1);
	usleep(1000 * philo->settings.meal_duration);
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
	gettimeofday(&philo->last_meal, NULL);
	while (1)
	{
		if (philo_eat(philo))
			free_exit(philo, 1);
		if (philo_sleep(philo))
			free_exit(philo, 1);
		gettimeofday(&time, NULL);
		if (print_msg(philo, &time, msg_is_thinking))
			free_exit(philo, 1);
	}
}
