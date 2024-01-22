/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:59:49 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 16:59:47 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <philo.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_philo		*philos;
	t_settings	settings;

	if (argc < 5)
		return (error("unsifficient number of arguments\n"
				"number_of_philosophers time_to_die time_to_eat time_to_sleep"
				" [number_of_times_each_philosopher_must_eat]"), 1);
	else if (argc > 6)
		return (error("too many arguments"), 1);
	if (parse_settings(&settings, argv + 1, argc))
		return (1);
	if (philo_alloc(&settings, &threads, &philos)
		|| philo_create(&settings, threads, philos))
		return (philo_free(&threads, &philos), 1);
	philo_free(&threads, &philos);
	return (0);
}
