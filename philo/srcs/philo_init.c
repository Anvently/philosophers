/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:33:04 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 18:05:08 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

static void	assign_forks(int nbr_philo, t_philo *philos, t_fork *forks)
{
	int	i;

	if (nbr_philo <= 0)
		return ;
	philos[0].left_fork = &forks[nbr_philo - 1];
	i = 0;
	while (nbr_philo > 1 && i < nbr_philo)
	{
		if (i != 0)
			philos[i].left_fork = &forks[i - 1];
		philos[i].right_fork = &forks[i];
		i++;
	}
}

static int	create_threads(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (error("error creating thread"), 1);
		i++;
	}
	return (0);
}

static int	init_philos(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		philos[i].number = i + 1;
		philos[i].settings = settings;
		if (pthread_mutex_init(&philos[i].local_mutex, NULL))
			return (error("error initializing mutex"), 1);
		i++;
	}
	return (0);
}

static int	wait_start(t_settings *settings)
{
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(&settings->count_mutex))
			return (pthread_mutex_unlock(&settings->begin_mutex), 1);
		if (settings->count == settings->nbr_philo)
		{
			if (pthread_mutex_unlock(&settings->count_mutex))
				return (pthread_mutex_unlock(&settings->begin_mutex), 1);
			break ;
		}
		if (pthread_mutex_unlock(&settings->count_mutex))
			return (pthread_mutex_unlock(&settings->begin_mutex), 1);
	}
	gettimeofday(&settings->begin_time, NULL);
	if (pthread_mutex_unlock(&settings->begin_mutex))
		return (1);
	return (0);
}

int	philo_start(t_settings *settings, t_philo *philos, t_fork *forks)
{
	pthread_t	monitor_tid;

	if (pthread_mutex_init(&settings->print_mutex, NULL)
		|| pthread_mutex_init(&settings->count_mutex, NULL)
		|| pthread_mutex_init(&settings->begin_mutex, NULL)
		|| pthread_mutex_lock(&settings->begin_mutex))
		return (error("error initializing mutex"), 1);
	assign_forks(settings->nbr_philo, philos, forks);
	if (init_philos(settings, philos)
		|| pthread_create(&monitor_tid, NULL, philo_monitor, philos))
		return (1);
	if (create_threads(settings, philos))
		return (1);
	usleep(1000);
	if (wait_start(settings))
		return (1);
	if (pthread_join(monitor_tid, NULL))
		return (1);
	return (0);
}
