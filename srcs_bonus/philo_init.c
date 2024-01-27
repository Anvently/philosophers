/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:41:43 by npirard           #+#    #+#             */
/*   Updated: 2024/01/27 12:58:03 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <semaphore.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

static int	init_philo(int i, t_philo *philo)
{
	char	*nbr_str;

	philo->number = i + 1;
	nbr_str = ft_itoa(i);
	if (!nbr_str)
		return (1);
	philo->sem_local_name = ft_strjoin("/local_", nbr_str);
	philo->sem_tready_name = ft_strjoin("/tready_", nbr_str);
	if (!philo->sem_local_name || !philo->sem_tready_name)
		return (free(nbr_str), 1);
	philo->sem_local = sem_open(philo->sem_local_name, O_CREAT, 0600, 0);
	if (sem_post(philo->sem_local))
		return (1);
	philo->sem_tready = sem_open(philo->sem_tready_name, O_CREAT, 0600, 0);
	if (philo->sem_local == SEM_FAILED
		|| philo->sem_tready == SEM_FAILED)
		return (1);
	return (0);
}

static int	philo_fork(t_philo *philo, pid_t *ids)
{
	pid_t	id;
	int		i;

	i = 0;
	while (i < philo->settings.nbr_philo)
	{
		id = fork();
		if (id < 0)
			return (-1);
		if (id == 0)
		{
			if (init_philo(i, philo))
				return (-1);
			return (0);
		}
		ids[i] = id;
		i++;
		usleep(10);
		sem_wait(philo->sem_pready);
	}
	return (id);
}

void	kill_all(pid_t *ids, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo && ids[i] != 0)
	{
		kill(ids[i], SIGINT);
		i++;
	}
}

static int	philo_wait(t_philo *philo, pid_t *ids)
{
	int	status;
	int	i;

	if (sem_wait(philo->sem_print))
		return (1);
	i = 0;
	while (i < (philo->settings.nbr_philo * 2) + 1)
	{
		if (sem_post(philo->sem_start))
			return (1);
		i++;
	}
	while (wait(&status))
		continue ;
	kill_all(ids, philo->settings.nbr_philo);
	return (0);
}

int	philo_start(t_philo *philo)
{
	pid_t	id;
	pid_t	*ids;

	ids = malloc(philo->settings.nbr_philo * sizeof(pid_t));
	if (!ids || !memset(ids, 0, sizeof(pid_t) * philo->settings.nbr_philo))
		return (1);
	philo->ids = ids;
	id = philo_fork(philo, ids);
	if (id == 0)
	{
		philo_routine(philo);
	}
	else if (id > 0)
	{
		if (init_end_monitor(philo) || philo_wait(philo, ids))
			return (kill_all(ids, philo->settings.nbr_philo), 1);
	}
	else if (id < 0)
		return (kill_all(ids, philo->settings.nbr_philo), 1);
	return (0);
}
