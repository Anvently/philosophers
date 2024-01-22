/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:57:48 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 18:09:51 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	philo_create(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (error("error creating thread"), 1);
		i++;
	}
	i = 0;
	while (i < settings->nbr_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (error("error joining threads"), 1);
		i++;
	}
	return (0);
}

int	philo_alloc(t_settings *settings, t_philo **philos_ptr)
{
	*philos_ptr = malloc(sizeof(t_philo) * settings->nbr_philo);
	if (!*philos_ptr)
		return (error("allocation error"), errno);
	memset(*philos_ptr, 0, sizeof(t_philo) * settings->nbr_philo);
	return (0);
}

void	philo_free(t_philo **philos_ptr)
{
	free(*philos_ptr);
	*philos_ptr = NULL;
}
