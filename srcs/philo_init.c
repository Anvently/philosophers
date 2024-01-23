/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:33:04 by npirard           #+#    #+#             */
/*   Updated: 2024/01/23 18:03:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

static void	assign_forks(int nbr_philo, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	if (nbr_philo <= 0)
		return ;
	philos[0].left_fork = &forks[nbr_philo - 1];
	i = 0;
	while (i < nbr_philo)
	{
		if (i != 0)
			philos[i].left_fork = &forks[i - 1];
		philos[i].right_fork = &forks[i];
		i++;
	}
}

static int	create_threads(t_settings *settings, t_philo *philos,
					pthread_mutex_t *print_mutex)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		philos[i].number = i + 1;
		philos[i].print_mutex = print_mutex;
		philos[i].settings = settings;
		if (pthread_mutex_init(&philos[i].local_mutex, NULL))
			return (error("error initializing mutex"), 1);
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (error("error creating thread"), 1);
		i++;
	}
	return (0);
}

int	philo_start(t_settings *settings, t_philo *philos,
			pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
	pthread_t	monitor_tid;

	if (pthread_mutex_init(print_mutex, NULL)
		|| pthread_mutex_init(&settings->count_mutex, NULL)
		|| pthread_mutex_init(&settings->begin_mutex, NULL)
		|| pthread_mutex_lock(&settings->begin_mutex))
		return (error("error initializing mutex"), 1);
	assign_forks(settings->nbr_philo, philos, forks);
	if (pthread_create(&monitor_tid, NULL, philo_monitor, (void *)philos)
		|| create_threads(settings, philos, print_mutex))
		return (1);
	while (settings->count != settings->nbr_philo)
		continue ;
	printf("BEGIN\n");
	gettimeofday(&settings->begin_time, NULL);
	pthread_mutex_unlock(&settings->begin_mutex);
	if (pthread_join(monitor_tid, NULL))
		return (1);
	return (0);
}
