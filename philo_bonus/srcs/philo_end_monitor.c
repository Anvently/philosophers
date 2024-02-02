/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:00:40 by npirard           #+#    #+#             */
/*   Updated: 2024/02/02 10:04:38 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

bool	philo_is_dead(t_philo *philo)
{
	if (sem_wait(philo->sem_local))
		return (true);
	if (philo->is_dead)
		return (true);
	if (sem_post(philo->sem_local))
		return (true);
	return (false);
}

static void	*check_end(t_philo *philo)
{
	int	count;

	count = philo->settings.nbr_philo;
	while (sem_wait(philo->sem_eaten_enough) == 0)
	{
		count--;
		if (count == 0)
		{
			kill_all(philo->ids, philo);
			break ;
		}
		usleep(10);
	}
	return (NULL);
}

static void	*philo_end_monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_post(philo->sem_print))
		return (NULL);
	if (sem_wait(philo->sem_start))
		return (NULL);
	check_end(philo);
	return (NULL);
}

void	kill_end_monitor(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->settings.nbr_philo)
	{
		sem_post(philo->sem_eaten_enough);
		i++;
	}
}

pthread_t	init_end_monitor(t_philo *philo)
{
	pthread_t	monitor_tid;

	if (pthread_create(&monitor_tid, NULL, philo_end_monitor, philo))
		return (0);
	return (monitor_tid);
}
