/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:57:48 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 17:30:59 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	philo_create(t_settings *settings, pthread_t *threads,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		philos[i].thread = &threads[i];
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]))
			return (error("error creating thread"), 1);
		i++;
	}
	sleep(1);
	return (0);
}

int	philo_alloc(t_settings *settings, pthread_t **threads_ptr,
		t_philo **philos_ptr)
{
	*threads_ptr = malloc(sizeof(pthread_t) * settings->nbr_philo);
	if (!*threads_ptr)
		return (error("allocation error"), errno);
	*philos_ptr = malloc(sizeof(t_philo) * settings->nbr_philo);
	if (!*philos_ptr)
	{
		free(*threads_ptr);
		return (error("allocation error"), errno);
	}
	memset(*threads_ptr, 0, sizeof(pthread_t) * settings->nbr_philo);
	memset(*philos_ptr, 0, sizeof(t_philo) * settings->nbr_philo);
	return (0);
}

void	philo_free(pthread_t **threads_ptr, t_philo **philos_ptr)
{
	free(*threads_ptr);
	free(*philos_ptr);
	*threads_ptr = NULL;
	*philos_ptr = NULL;
}
