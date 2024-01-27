/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:10:56 by npirard           #+#    #+#             */
/*   Updated: 2024/01/27 12:59:06 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	check_death(t_philo *philo)
{
	t_timeval	time;
	t_timeval	last_time;

	gettimeofday(&time, NULL);
	if (sem_wait(philo->sem_local))
		return (1);
	last_time = philo->last_meal;
	if (sem_post(philo->sem_local))
		return (1);
	if (check_time(&time, &last_time, philo->settings.time_to_die))
	{
		if (print_msg(philo, &time, msg_died))
			return (1);
		return (-1);
	}
	return (0);
}

void	free_exit(t_philo *philo, int status)
{
	free_philo(philo);
	exit(status);
}

static void	*philo_monitor(void *data)
{
	t_philo		*philo;
	int			ret;

	philo = (t_philo *)data;
	if (sem_post(philo->sem_tready))
		free_exit(philo, 1);
	if (sem_wait(philo->sem_start))
		free_exit(philo, 1);
	gettimeofday(&philo->last_meal, NULL);
	while (1)
	{
		ret = check_death(philo);
		if (ret > 0)
			free_exit(philo, 1);
		if (ret < 0)
			free_exit(philo, -1);
		usleep(100);
	}
	return (NULL);
}

int	init_monitor(t_philo *philo)
{
	pthread_t	tid_monitor;

	if (pthread_create(&tid_monitor, NULL, philo_monitor, philo))
		return (1);
	if (sem_wait(philo->sem_tready))
		return (1);
	return (0);
}
