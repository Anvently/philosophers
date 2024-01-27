/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:59:49 by npirard           #+#    #+#             */
/*   Updated: 2024/01/27 13:08:45 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <philo.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_settings		settings;
	pthread_mutex_t	*forks;

	if (argc < 5)
		return (error("unsifficient number of arguments\n"
				"number_of_philosophers time_to_die time_to_eat time_to_sleep"
				" [number_of_times_each_philosopher_must_eat]"), 1);
	else if (argc > 6)
		return (error("too many arguments"), 1);
	memset(&settings, 0, sizeof(t_settings));
	if (parse_settings(&settings, argv + 1, argc))
		return (1);
	if (settings.nbr_philo == 0)
		return (0);
	philos = NULL;
	forks = NULL;
	if (philo_alloc(&settings, &philos) || fork_alloc(&settings, &forks)
		|| philo_start(&settings, philos, forks))
		return (philo_free(&settings, &philos, &forks), 1);
	philo_free(&settings, &philos, &forks);
	return (0);
}
