/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:59:49 by npirard           #+#    #+#             */
/*   Updated: 2024/02/02 10:04:29 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <philo_bonus.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc < 5)
		return (error("unsifficient number of arguments\n"
				"number_of_philosophers time_to_die time_to_eat time_to_sleep"
				" [number_of_times_each_philosopher_must_eat]"), 1);
	else if (argc > 6)
		return (error("too many arguments"), 1);
	memset(&philo, 0, sizeof(t_philo));
	if (parse_settings(&philo.settings, argv + 1, argc))
		return (1);
	if (philo.settings.nbr_philo == 0)
		return (0);
	if (init_sem(&philo))
		return (error("error initializing semaphores"), free_philo(&philo), 1);
	if (philo_start(&philo))
	{
		free_philo(&philo);
		return (1);
	}
	free_philo(&philo);
	return (0);
}
