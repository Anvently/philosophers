/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:24:52 by npirard           #+#    #+#             */
/*   Updated: 2024/01/24 14:42:49 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philo.h>
#include <stdio.h>
#include <string.h>

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->local_mutex);
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->local_mutex);
}

bool	philo_is_dead(t_philo *philo)
{
	bool	ret;

	ret = false;
	if (pthread_mutex_lock(&philo->local_mutex))
	{
		philo->is_dead = true;
		return (true);
	}
	if (philo->is_dead)
		ret = true;
	else
		ret = false;
	if (pthread_mutex_unlock(&philo->local_mutex))
	{
		philo->is_dead = true;
		return (true);
	}
	return (ret);
}

static int	philo_eat(t_philo *philo)
{
	if (take_both_forks(philo))
		return (1);
	if (print_msg(philo, msg_is_eating))
		return (philo_die(philo), 1);
	usleep(philo->settings->meal_duration * 1000);
	if (unlock_forks(philo))
		return (philo_die(philo), 1);
	if (philo_is_dead(philo))
		return (1);
	if (pthread_mutex_lock(&philo->local_mutex))
		return (philo_die(philo), 1);
	gettimeofday(&philo->last_meal, NULL);
	philo->nbr_meals++;
	if (philo->nbr_meals == philo->settings->nbr_meal_to_end)
	{
		if (pthread_mutex_unlock(&philo->local_mutex))
			return (philo_die(philo), 1);
		if (print_msg(philo, msg_ended))
			return (philo_die(philo), 1);
		return (0);
	}
	if (pthread_mutex_unlock(&philo->local_mutex))
		return (philo_die(philo), 1);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (print_msg(philo, msg_is_sleeping))
		return (philo_die(philo), 1);
	usleep(philo->settings->sleep_duration * 1000);
	if (philo_is_dead(philo))
		return (1);
	gettimeofday(&philo->last_sleep, NULL);
	return (0);
}

/// @brief
/// @param data
/// @return
void	*philo_routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (pthread_mutex_lock(&philo->settings->count_mutex)
		|| !(++philo->settings->count)
		|| pthread_mutex_unlock(&philo->settings->count_mutex))
		return (philo_die(philo), NULL);
	if (pthread_mutex_lock(&philo->settings->begin_mutex)
		|| pthread_mutex_unlock(&philo->settings->begin_mutex))
		return (philo_die(philo), NULL);
	while (1)
	{
		if (philo_is_dead(philo) || philo_eat(philo))
			return (NULL);
		if (philo_is_dead(philo) || philo_sleep(philo))
			return (NULL);
		if (philo_is_dead(philo) || print_msg(philo, msg_is_thinking))
			return (NULL);
	}
	return (NULL);
}
