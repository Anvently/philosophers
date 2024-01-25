/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:27:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/25 16:29:55 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdio.h>

bool	check_time(t_timeval *time,t_timeval *last_time, int max)
{
	gettimeofday(time, NULL);
	if (time->tv_sec == last_time->tv_sec)
	{
		if ((time->tv_usec - last_time->tv_usec) >= (long)(max * 1000))
			return (true);
		return (false);
	}
	else if ((time->tv_sec - last_time->tv_sec > 1)
		&& ((time->tv_sec - last_time->tv_sec) * 1000 >= max))
		return (true);
	else if ((time->tv_sec - last_time->tv_sec == 1)
		&& (time->tv_usec + (1000000 - last_time->tv_usec))
		>= (long)(max * 1000))
		return (true);
	return (false);
}
