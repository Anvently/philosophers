/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:59:49 by npirard           #+#    #+#             */
/*   Updated: 2024/01/28 18:06:52 by npirard          ###   ########.fr       */
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

static int	init_sem(t_philo *philo)
{
	int	i;

	errno = 0;
	philo->sem_eaten_enough = sem_open("/eaten_enough", O_CREAT, 0600, 0);
	philo->sem_forks = sem_open("/forks", O_CREAT, 0600, 0);
	i = 0;
	while (i < philo->settings.nbr_philo / 2)
	{
		if (sem_post(philo->sem_forks))
			return (1);
		i++;
	}
	philo->sem_pready = sem_open("/pready", O_CREAT, 0600, 0);
	philo->sem_print = sem_open("/print", O_CREAT, 0600, 0);
	if (sem_post(philo->sem_print))
		return (1);
	philo->sem_start = sem_open("/start", O_CREAT, 0600, 0);
	if (philo->sem_eaten_enough == SEM_FAILED
		|| philo->sem_forks == SEM_FAILED
		|| philo->sem_pready == SEM_FAILED
		|| philo->sem_print == SEM_FAILED
		|| philo->sem_start == SEM_FAILED)
		return (1);
	return (0);
}

static void	free_sem(t_philo *philo)
{
	if (philo->sem_forks)
	{
		sem_unlink("forks");
		sem_close(philo->sem_forks);
	}
	if (philo->sem_print)
	{
		sem_unlink("print");
		sem_close(philo->sem_print);
	}
	if (philo->sem_start)
	{
		sem_unlink("start");
		sem_close(philo->sem_start);
	}
	if (philo->sem_pready)
	{
		sem_unlink("pready");
		sem_close(philo->sem_pready);
	}
	if (philo->sem_eaten_enough)
	{
		sem_unlink("eaten_enough");
		sem_close(philo->sem_eaten_enough);
	}
}

static void	free_local_sem(t_philo *philo)
{
	if (philo->sem_tready)
	{
		sem_unlink(philo->sem_tready_name);
		sem_close(philo->sem_tready);
	}
	if (philo->sem_local_name)
	{
		sem_unlink(philo->sem_local_name);
		sem_close(philo->sem_eaten_enough);
	}
}

void	free_philo(t_philo *philo)
{
	free_sem(philo);
	free_local_sem(philo);
	if (philo->ids)
		free(philo->ids);
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	printf("PID = %d", getpid());
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
