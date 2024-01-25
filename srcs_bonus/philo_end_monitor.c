/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:00:40 by npirard           #+#    #+#             */
/*   Updated: 2024/01/25 19:09:09 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void	check_end(t_philo *philo)
{
	int	count;

	count = philo->settings.nbr_philo;
	while (sem_wait(philo->sem_eaten_enough) == 0)
	{
		count--;
		if (count == 0)
		{
			kill_all(philo->ids, philo->settings.nbr_philo);
			free_exit(philo, 1);
		}
	}
}

static void	*philo_end_monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_post(philo->sem_print))
		return (NULL);
	check_end(philo);
	return (NULL);
}

int	init_end_monitor(t_philo *philo)
{
	pthread_t	monitor_tid;

	if (pthread_create(&monitor_tid, NULL, philo_end_monitor, philo))
		return (1);
	if (sem_wait(philo->sem_start))
		return (1);
	printf("PING\n");
	return (0);
}
