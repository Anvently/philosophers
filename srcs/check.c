/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:27:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/24 15:47:48 by npirard          ###   ########.fr       */
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
