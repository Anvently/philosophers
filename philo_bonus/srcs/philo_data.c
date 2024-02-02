/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:09:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/02 17:55:09 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

void	unlink_sem(char *local_name, char *tready_name)
{
	if (!local_name && !tready_name)
	{
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_unlink("/start");
		sem_unlink("/pready");
		sem_unlink("/eaten");
	}
	if (local_name)
		sem_unlink(local_name);
	if (tready_name)
		sem_unlink(tready_name);
}

static void	free_sem(t_philo *philo)
{
	if (philo->sem_forks)
		sem_close(philo->sem_forks);
	if (philo->sem_print)
		sem_close(philo->sem_print);
	if (philo->sem_start)
		sem_close(philo->sem_start);
	if (philo->sem_pready)
		sem_close(philo->sem_pready);
	if (philo->sem_eaten_enough)
		sem_close(philo->sem_eaten_enough);
	if (philo->sem_tready)
		sem_close(philo->sem_tready);
	if (philo->sem_local)
		sem_close(philo->sem_local);
}

int	init_sem(t_philo *philo)
{
	unlink_sem(NULL, NULL);
	errno = 0;
	philo->sem_eaten_enough = sem_open("/eaten", O_CREAT, 0600, 0);
	philo->sem_forks = sem_open("/forks", O_CREAT, 0600,
			philo->settings.nbr_philo / 2);
	philo->sem_pready = sem_open("/pready", O_CREAT, 0600, 0);
	philo->sem_print = sem_open("/print", O_CREAT, 0600, 1);
	philo->sem_start = sem_open("/start", O_CREAT, 0600, 0);
	unlink_sem(NULL, NULL);
	if (philo->sem_eaten_enough == SEM_FAILED
		|| philo->sem_forks == SEM_FAILED
		|| philo->sem_pready == SEM_FAILED
		|| philo->sem_print == SEM_FAILED
		|| philo->sem_start == SEM_FAILED)
		return (1);
	return (0);
}

void	free_philo(t_philo *philo)
{
	free_sem(philo);
	if (philo->ids)
		free(philo->ids);
}
