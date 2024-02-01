/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:10:56 by npirard           #+#    #+#             */
/*   Updated: 2024/02/01 18:29:31 by npirard          ###   ########.fr       */
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
	if (check_time(&time, &last_time, philo->settings.time_to_die))
	{
		philo->is_dead = true;
		if (sem_post(philo->sem_local))
			return (1);
		if (print_msg(philo, &time, msg_died))
			return (1);
		return (-1);
	}
	if (sem_post(philo->sem_local))
		return (1);
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
		return (NULL);
	if (sem_wait(philo->sem_start))
		return (NULL);
	if (sem_wait(philo->sem_local))
		return (NULL);
	gettimeofday(&philo->last_meal, NULL);
	if (sem_post(philo->sem_local))
		return (NULL);
	usleep(100);
	while (1)
	{
		ret = check_death(philo);
		if (ret > 0)
			return (NULL);
		if (ret < 0)
			return (NULL);
	}
	return (NULL);
}

int	init_monitor(t_philo *philo)
{
	pthread_t	tid_monitor;

	if (pthread_create(&tid_monitor, NULL, philo_monitor, philo)
		|| pthread_detach(tid_monitor))
		return (1);
	if (sem_wait(philo->sem_tready))
		return (1);
	return (0);
}
