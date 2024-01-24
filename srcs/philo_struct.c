/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:57:48 by npirard           #+#    #+#             */
/*   Updated: 2024/01/24 14:23:19 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	philo_alloc(t_settings *settings, t_philo **philos_ptr)
{
	*philos_ptr = malloc(sizeof(t_philo) * settings->nbr_philo);
	if (!*philos_ptr)
		return (error("allocation error"), errno);
	memset(*philos_ptr, 0, sizeof(t_philo) * settings->nbr_philo);
	return (0);
}

int	fork_alloc(t_settings *settings, pthread_mutex_t **forks_ptr)
{
	int	i;

	*forks_ptr = malloc(sizeof(pthread_mutex_t) * settings->nbr_philo);
	if (!*forks_ptr)
		return (error("allocation error"), errno);
	memset(*forks_ptr, 0, sizeof(pthread_mutex_t) * settings->nbr_philo);
	i = 0;
	while (i < settings->nbr_philo)
	{
		if (pthread_mutex_init(&(*forks_ptr)[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	philo_free(t_settings *settings, t_philo **philos_ptr,
			pthread_mutex_t **forks_ptr)
{
	int	i;

	if (*philos_ptr)
	{
		i = 0;
		while (i < settings->nbr_philo)
			pthread_mutex_destroy(&(*philos_ptr)[i++].local_mutex);
		free(*philos_ptr);
	}
	*philos_ptr = NULL;
	if (*forks_ptr)
	{
		i = 0;
		while (i < settings->nbr_philo)
			pthread_mutex_destroy(&(*forks_ptr)[i++]);
		free(*forks_ptr);
	}
	pthread_mutex_destroy(&settings->count_mutex);
	pthread_mutex_destroy(&settings->begin_mutex);
	pthread_mutex_destroy(&settings->print_mutex);
	*forks_ptr = NULL;
}

void	philo_print(int nbr_philo, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		printf("%2$-*1$s : %3$*1$d\n"
			"%4$-*1$s : %5$*1$d\n"
			"%6$-*1$s : %7$*1$ld\n"
			"%8$-*1$s : %9$*1$ld\n"
			"%10$-*1$s : %11$*1$d\n"
			"%12$-*1$s : %13$*1$lu\n"
			"%14$-*1$s : %15$*1$p\n"
			"%16$-*1$s : %17$*1$p\n\n",
			20, "Philosopher number", philos[i].number,
			"Is dead", philos[i].is_dead,
			"Last sleep (us)", philos[i].last_sleep.tv_usec,
			"Last meal (us)", philos[i].last_meal.tv_usec,
			"Number of meals", philos[i].nbr_meals,
			"Thread id", philos[i].thread,
			"Left fork", philos[i].left_fork,
			"Right fork", philos[i].right_fork);
		i++;
	}
}
