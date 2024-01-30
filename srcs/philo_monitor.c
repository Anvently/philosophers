/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:47 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 13:14:33 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

static int	join_threads(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (error("error joining threads"), 1);
		i++;
	}
	return (0);
}

static int	philo_check_status(t_philo *philo)
{
	int			ret;
	t_timeval	time;

	ret = 0;
	if (pthread_mutex_lock(&philo->local_mutex))
		return (1);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&philo->local_mutex), 1);
	if (philo->last_meal.tv_sec == 0)
			philo->last_meal = philo->settings->begin_time;
	gettimeofday(&time, NULL);
	if (check_time(&philo->last_meal, philo->settings->time_to_die))
		return (pthread_mutex_unlock(&philo->local_mutex),
			print_msg(philo, &time, msg_died), 1);
	if (philo->settings->nbr_meal_to_end < 0
		|| philo->nbr_meals < philo->settings->nbr_meal_to_end)
		ret = -1;
	if (pthread_mutex_unlock(&philo->local_mutex))
		return (1);
	return (ret);
}

static void	kill_all(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
		philo_die(&philos[i++]);
}

static int	check_all_philos(t_settings *settings, t_philo *philos)
{
	int		i;
	int		ret;
	int		is_end;

	i = 0;
	is_end = 1;
	while (i < settings->nbr_philo)
	{
		ret = philo_check_status(&philos[i++]);
		if (ret > 0)
			return (1);
		else if (ret < 0)
			is_end = 0;
	}
	return (is_end);
}

void	*philo_monitor(void *data)
{
	t_philo		*philos;
	t_settings	*settings;

	philos = (t_philo *)data;
	settings = philos[0].settings;
	if (pthread_mutex_lock(&settings->begin_mutex)
		|| pthread_mutex_unlock(&settings->begin_mutex))
		return (NULL);
	while (1)
	{
		if (check_all_philos(settings, philos))
		{
			kill_all(settings, philos);
			join_threads(settings, philos);
			return (NULL);
		}
		usleep(10);
		continue ;
	}
	return (NULL);
}
