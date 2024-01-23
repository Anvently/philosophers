/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:47 by npirard           #+#    #+#             */
/*   Updated: 2024/01/23 18:36:37 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&philo->local_mutex))
		return (1);
	if (philo->last_meal.tv_sec == 0)
			philo->last_meal = philo->settings->begin_time;
	if (check_time(&philo->last_meal, philo->settings->time_to_die))
		return (pthread_mutex_unlock(&philo->local_mutex),
			print_msg(philo, msg_died), 1);
	if (philo->nbr_meals < philo->settings->nbr_meal_to_end)
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
	bool	is_end;

	i = 0;
	is_end = true;
	while (i < settings->nbr_philo)
	{
		ret = philo_check_status(&philos[i++]);
		if (ret > 0)
			return (1);
		else if (ret < 0)
			is_end = false;
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
			return (kill_all(settings, philos), NULL);
		continue ;
	}
	if (join_threads(settings, philos))
		return (NULL);
	return (NULL);
}
