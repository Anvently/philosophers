/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:27:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 12:30:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

bool	philo_check_dead(t_settings *settings, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < settings->nbr_philo)
	{
		if (philos[i].is_dead)
			return (true);
		i++;
	}
	return (false);
}

bool	check_time(t_timeval *last_time, int max)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	if (time.tv_sec == last_time->tv_sec)
	{
		if ((time.tv_usec - last_time->tv_usec) >= (long)(max * 1000))
			return (true);
		return (false);
	}
	else if ((time.tv_sec - last_time->tv_sec > 1)
		&& ((time.tv_sec - last_time->tv_sec) * 1000 >= max))
		return (true);
	else if ((time.tv_sec - last_time->tv_sec == 1)
		&& (time.tv_usec + (1000000 - last_time->tv_usec))
		>= (long)(max * 1000))
		return (true);
	return (false);
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

void	usleep_calc(t_timeval *start_time, int duration)
{
	t_timeval	time;
	int			diff_sec;
	long		diff_usec;
	long long	sleep_time;

	gettimeofday(&time, NULL);
	diff_sec = time.tv_sec - start_time->tv_sec;
	if (diff_sec)
	{
		diff_usec = (1000000 - start_time->tv_usec) + time.tv_usec;
		sleep_time = duration * 1000 - (diff_sec * 1000000 + diff_usec);
		if (usleep(sleep_time))
			usleep(sleep_time);
	}
	else
	{
		diff_usec = time.tv_usec - start_time->tv_usec;
		sleep_time = duration * 1000 - diff_usec;
		if (sleep_time > 0)
			usleep(sleep_time);
	}
}
