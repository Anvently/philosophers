/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:27:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/23 14:41:39 by npirard          ###   ########.fr       */
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
	/* dprintf(2, "Last time: sec = %ld | usec = %ld\n"
		"Time: sec = %ld | usec = %ld", last_time->tv_sec,
		last_time->tv_usec, time.tv_sec, time.tv_usec); */
	if (time.tv_sec == last_time->tv_sec)
	{
		if ((time.tv_usec - last_time->tv_usec) >= (long)(max * 1000))
			return (true);
		return (false);
	}
	if ((time.tv_sec - last_time->tv_sec) * 1000 >= max)
		return (true);
	return (false);

}
